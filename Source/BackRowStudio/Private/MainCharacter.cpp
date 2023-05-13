// Fill out your copyright notice in the Description page of Project Settings.


#include "BackRowStudio/Public/MainCharacter.h"
#include "BaseSpellActor.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Camera/CameraComponent.h"
#include "CheckpointActor.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Enemy.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "HealthBarWidget.h"
#include "InventoryComponent.h"
#include "InventoryWidget.h"
#include "ItemActor.h"
#include "Kismet/GameplayStatics.h"
#include "MinimapWidget.h"
#include "PauseWidget.h"
#include "Wolf.h"
#include "Components/SphereComponent.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Spring Arm Setup
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->TargetArmLength = 800.f;
    SpringArmComponent->SetWorldRotation((FRotator(-60.f, 0.f, 0.f)));
    SpringArmComponent->bUsePawnControlRotation = true;

    // Camera Setup
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    CameraComponent->SetupAttachment(SpringArmComponent);
    CameraComponent->SetFieldOfView(90);


    // Player Setup
    const auto characterMovementComponent = GetCharacterMovement();
    characterMovementComponent->MaxAcceleration = 10000.f;
    characterMovementComponent->BrakingFrictionFactor = 1000.f;
    characterMovementComponent->MaxWalkSpeed = 800.f;
    AutoPossessPlayer = EAutoReceiveInput::Player0;

    // Spell Setup
    SpellEnenhancements = CreateDefaultSubobject<ABaseSpellActor>(TEXT("ArcaneEnhancement"));
    // GroundSpellLocation = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ground Spell Location"));
    // GroundSpellLocation->SetupAttachment(GetRootComponent());
    // FVector rootLocation = GetRootComponent()->GetRelativeLocation();
    // GroundSpellLocation->SetRelativeLocation(FVector(rootLocation.X, rootLocation.Y, rootLocation.Z - 80));

    // Minimap Spring Arm Setup
    MiniMapSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Minimap SpringArm"));
    MiniMapSpringArm->SetupAttachment(GetRootComponent());
    MiniMapSpringArm->TargetArmLength = 900.f;
    MiniMapSpringArm->SetWorldRotation((FRotator(-90.f, 0.f, 0.f)));
    MiniMapSpringArm->bInheritPitch = 0;
    MiniMapSpringArm->bInheritRoll = 0;
    MiniMapSpringArm->bInheritYaw = 0;

    // Minimap Scene Capture Setup
    MinimapCam = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("MiniMapCamera"));
    MinimapCam->SetupAttachment(MiniMapSpringArm);
    MinimapCam->ProjectionType = ECameraProjectionMode::Orthographic;
    MinimapCam->OrthoWidth = 2500.f;

    // Inventory Component Setup
    MyInv = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory Component"));
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
    Super::BeginPlay();

    OpenOrClosePause = true;

    GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMainCharacter::OnOverlapBegin);

    // Adding mapping context component
    if (const auto *controller = Cast<APlayerController>(Controller))
    {
        if (auto *inputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(controller->GetLocalPlayer()))
        {
            inputSystem->AddMappingContext(MappingContextComponent, 0);
        }
    }

    if (MiniMapWidgetTemplate)
    {
        // seems like a bug that this doesn't work (doesn't display the widget on the screen)
        MinimapWidget = CreateWidget<UMinimapWidget>(GetWorld(), MiniMapWidgetTemplate, FName("Minimap"));
        MinimapWidget->AddToViewport();
    }
    if (MyHealthWidget)
    {
        // seems like a bug that this doesn't work (doesn't display the widget on the screen)
        HealthBarWidget = CreateWidget<UHealthBarWidget>(GetWorld(), MyHealthWidget, FName("Healthbar"));
        HealthBarWidget->MyPlayer = this;
        HealthBarWidget->AddToViewport();
    }

    if (APlayerController *TempPC = Cast<APlayerController>(GetController()))
    {
        PC = TempPC;
    }

    if (MyPauseMenu->IsValidLowLevel())
    {
        PauseMenu = CreateWidget<UPauseWidget>(GetWorld(), MyPauseMenu, FName("Inventory Widget"));
        PauseMenu->PC = PC;
        PauseMenu->AddToViewport();
        PauseMenu->SetVisibility(ESlateVisibility::Collapsed);
    }
}

// Input action Functions
void AMainCharacter::MoveAction(const FInputActionValue &value)
{
    const auto movementVector = value.Get<FVector2D>();

    if (GetController())
    {
        const auto rotation = Controller->GetControlRotation();
        const FRotator yawRotation(0.f, rotation.Yaw, 0.f);

        // Getting forward vector + forward movement
        const FVector forwardDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(forwardDirection, movementVector.Y);

        // Getting right vector + right movement
        const FVector rightDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
        AddMovementInput(rightDirection, movementVector.X);
    }
}

void AMainCharacter::LookAroundAction(const FInputActionValue &value)
{
    const FVector2D lookAxisValue = value.Get<FVector2D>();

    if (GetController())
    {
        AddControllerYawInput(lookAxisValue.X);
        AddControllerPitchInput(lookAxisValue.Y);
    }
}

void AMainCharacter::JumpAction(const FInputActionValue &value) { Super::Jump(); }

void AMainCharacter::LightAttackAction(const FInputActionValue &value)
{
    if (CanJump())
        SpellEnenhancements->CastSpell(GetActorLocation(), GetActorRotation(), GetWorld(), GetRootComponent(), false);
}

void AMainCharacter::HeavyAttackAction(const FInputActionValue &value)
{
    if (!MyInv->Spells[SelectedSpell].Item)
    {
        return;
    }

    if (CanJump())
    {
        if (SpellEnenhancements->Spell->Heavy.IsGroundSpell)
            SpellEnenhancements->CastSpell(FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - GroundSpellLocationOffset), GetActorRotation(), GetWorld(), GetRootComponent(), true);
        else
            SpellEnenhancements->CastSpell(GetActorLocation(), GetActorRotation(), GetWorld(), GetRootComponent(), true);
    }
}

void AMainCharacter::AbilityKeyAction(const FInputActionValue &value)
{
    SelectedSpell = static_cast<int>(value.Get<float>()) - 1;
    SetSpell();
}

void AMainCharacter::AbilityScrollAction(const FInputActionValue &value)
{
    SelectedSpell += static_cast<int>(value.Get<float>());
    if (SelectedSpell < 0)
        SelectedSpell = 3;

    if (SelectedSpell > 3)
        SelectedSpell = 0;

    SetSpell();
}

void AMainCharacter::SetSpell()
{
    auto spellItem = MyInv->Spells[SelectedSpell].Item;
    if (!spellItem)
        return;

    auto spell = spellItem->Spell;
    if (!spell)
        return;

    SpellEnenhancements->Spell = spell;
    SpellEnenhancements->SetData();
}

void AMainCharacter::OpenCloseInventory(const FInputActionValue &value)
{
    if (MyInv->IsValidLowLevel())
    {
        if (OpenInventory)
        {
            if (MyInvWidget)
            {
                InvWidget = CreateWidget<UInventoryWidget>(GetWorld(), MyInvWidget, FName("Inventory Widget"));
                InvWidget->Inventory = MyInv;
                InvWidget->AddToViewport();
                if (PC)
                {
                    PC->SetShowMouseCursor(true);
                    UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PC, InvWidget);
                }
            }
            OpenInventory = false;
        }
        else
        {
            if (InvWidget)
            {
                InvWidget->RemoveFromParent();
            }

            if (PC)
            {
                PC->SetShowMouseCursor(false);
                UWidgetBlueprintLibrary::SetInputMode_GameOnly(PC);
            }

            OpenInventory = true;
        }
    }
}

void AMainCharacter::OpenClosePauseMenu(const FInputActionValue &value)
{
    if (MyPauseMenu->IsValidLowLevel())
    {
        if (OpenOrClosePause)
        {
            PauseMenu->DoOnCreate();
            OpenOrClosePause = false;
        }
        else
        {
            PauseMenu->DoOnDestroy();
            OpenOrClosePause = true;
        }
    }
}

void AMainCharacter::AttachSpellComponents(/*TSubclassOf<ABaseSpellActor> SpellActors, */ FName socket_name) { SpellEnenhancements->AttachToComponent(GetRootComponent(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), FName(socket_name)); }

void AMainCharacter::OnOverlapBegin(UPrimitiveComponent *overlapped_component, AActor *other_actor, UPrimitiveComponent *other_component, int other_index, bool from_sweep, const FHitResult &sweep_result)
{
    if (const auto item = Cast<AItemActor>(other_actor))
    {
        if (item->Item != nullptr && !item->IsPickedUp)
        {
            if (item->Item->Spell == nullptr)
            {
                if (MyInv->AddItem(FSlotStruct(item->Item, 1)))
                {
                    UGameplayStatics::PlaySound2D(this, PickupSound);
                }
            }
            else
            {
                if (MyInv->AddSpell(FSlotStruct(item->Item, 1)))
                {
                    SetSpell();
                    UGameplayStatics::PlaySound2D(this, PickupSound);
                }
            }
            item->IsPickedUp = true;
            item->Mesh->SetVisibility(false);
            item->SphereCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        }
    }
}

// Called every frame
void AMainCharacter::Tick(float delta_time) { Super::Tick(delta_time); }

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent *input_component)
{
    Super::SetupPlayerInputComponent(input_component);

    // Setting up Player Input Action Mappings
    if (auto *enhancedInputComponent = CastChecked<UEnhancedInputComponent>(input_component))
    {
        // Player Move
        enhancedInputComponent->BindAction(InputActionMove, ETriggerEvent::Triggered, this, &AMainCharacter::MoveAction);

        // Player Look Around
        enhancedInputComponent->BindAction(InputActionLookAround, ETriggerEvent::Triggered, this, &AMainCharacter::LookAroundAction);

        // Player Jump
        enhancedInputComponent->BindAction(InputActionJump, ETriggerEvent::Triggered, this, &AMainCharacter::JumpAction);

        // Player Light Attack
        enhancedInputComponent->BindAction(InputActionLightAttack, ETriggerEvent::Triggered, this, &AMainCharacter::LightAttackAction);

        // Player Heavy Attack
        enhancedInputComponent->BindAction(InputActionHeavyAttack, ETriggerEvent::Triggered, this, &AMainCharacter::HeavyAttackAction);

        // Player Ability Keys
        enhancedInputComponent->BindAction(InputActionAbilityKey, ETriggerEvent::Triggered, this, &AMainCharacter::AbilityKeyAction);

        // Player Ability Scroll Functions
        enhancedInputComponent->BindAction(InputActionScrollAbility, ETriggerEvent::Triggered, this, &AMainCharacter::AbilityScrollAction);

        // Player Open or Close Inventory keys
        enhancedInputComponent->BindAction(InputActionOpenCloseInventory, ETriggerEvent::Started, this, &AMainCharacter::OpenCloseInventory);

        // Player Open or Close Inventory keys
        enhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &AMainCharacter::OpenClosePauseMenu);
    }
}

void AMainCharacter::SetCheckpoint(const ACheckpointActor *checkpoint) { RespawnLocation = checkpoint->SpawnPoint->GetComponentToWorld().GetLocation(); }
