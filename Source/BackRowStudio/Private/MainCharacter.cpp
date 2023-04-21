// Fill out your copyright notice in the Description page of Project Settings.


#include "BackRowStudio/Public/MainCharacter.h"
#include "BaseSpellActor.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "InventoryComponent.h"
#include "InventoryWidget.h"
#include "MinimapWidget.h"

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
    auto CharacterMovementComponent = GetCharacterMovement();
    CharacterMovementComponent->MaxAcceleration = 10000.f;
    CharacterMovementComponent->BrakingFrictionFactor = 1000.f;
    CharacterMovementComponent->MaxWalkSpeed = 800.f;
    AutoPossessPlayer = EAutoReceiveInput::Player0;

    // Spell Setup
    SpellEnenhancements = CreateDefaultSubobject<ABaseSpellActor>(TEXT("ArcaneEnhancement"));
    // ArcaneEnhancement->AttachToActor( )

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
    const ConstructorHelpers::FObjectFinder<UTextureRenderTarget2D> minimapRenderFinder(TEXT("/Script/Engine.TextureRenderTarget2D'/Game/IndividualFolders/Dennis/MiniMap/MiniMapRenderTarget.MiniMapRenderTarget'"));
    MinimapCam->TextureTarget = ToObjectPtr(minimapRenderFinder.Object);

    // Minimap Widget Setup
    const ConstructorHelpers::FObjectFinder<UMaterial> minimapMatFinder(TEXT("/Script/Engine.Material'/Game/IndividualFolders/Dennis/MiniMap/MiniMapMat.MiniMapMat'"));
    Mat = minimapMatFinder.Object;

    // Inventory Component Setup
    MyInv = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory Component"));
}


// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
    Super::BeginPlay();

    // Adding mapping context component
    APlayerController *PlayerController = Cast<APlayerController>(Controller);
    if (PlayerController)
    {
        UEnhancedInputLocalPlayerSubsystem *Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
        if (Subsystem)
        {
            Subsystem->AddMappingContext(MappingContextComponent, 0);
        }
    }
    if (MiniMapWidgetTemplate && Mat)
    {
        // seems like a bug that this doesn't work (doesn't display the widget on the screen)
        MinimapWidget = CreateWidget<UMinimapWidget>(GetWorld(), MiniMapWidgetTemplate, FName("Minimap"));
        MinimapWidget->MyMat = Mat;
        MinimapWidget->AddToViewport();
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("invalid Material or MiniMapWidgetTemplate"));
    }
    if (APlayerController *TempPC = Cast<APlayerController>(GetController()))
    {
        PC = TempPC;
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("My Controller Is Not A PlayerController"));
    }
}

// Input action Functions
void AMainCharacter::MoveAction(const FInputActionValue &Value)
{
    const FVector2D MovementVector = Value.Get<FVector2D>();

    if (GetController())
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

        // Getting forward vector + forward movement
        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(ForwardDirection, MovementVector.Y);

        // Getting right vector + right movement
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        AddMovementInput(RightDirection, MovementVector.X);
    }
}

void AMainCharacter::LookAroundAction(const FInputActionValue &Value)
{
    const FVector2D LookAxisValue = Value.Get<FVector2D>();

    if (GetController())
    {
        AddControllerYawInput(LookAxisValue.X);
        AddControllerPitchInput(LookAxisValue.Y);
    }
}

void AMainCharacter::JumpAction(const FInputActionValue &Value) { Super::Jump(); }

void AMainCharacter::LightAttackAction(const FInputActionValue &Value) {}

void AMainCharacter::HeavyAttackAction(const FInputActionValue &Value) {}

void AMainCharacter::AbilityKeyAction(const FInputActionValue &Value)
{
    SelectedSpell = static_cast<int>(Value.Get<float>()) - 1;
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Selected Spell: %d"), SelectedSpell));
}

void AMainCharacter::AbilityScrollAction(const FInputActionValue &Value)
{
    SelectedSpell += static_cast<int>(Value.Get<float>());
    if (SelectedSpell < 0)
        SelectedSpell = 3;
    if (SelectedSpell > 3)
        SelectedSpell = 0;
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Selected Spell: %d"), SelectedSpell));
}

void AMainCharacter::OpenCloseInventory(const FInputActionValue &Value)
{
    if (MyInv->IsValidLowLevel())
    {
        if (CanOpenInventory)
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
                else
                {
                    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("My Inventory Widget Is Invalid"));
                }
                OpenInventory = false;
            }
            else
            {
                // GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("TEST"));
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
            CanOpenInventory = false;
        }
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("My Inventory Is Invalid"));
    }
}

void AMainCharacter::AttachSpellComponents(/*TSubclassOf<ABaseSpellActor> SpellActors, */ FName SocketName)
{
    SpellEnenhancements->AttachToComponent(GetRootComponent(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), FName(SocketName));
}

void AMainCharacter::OpenCloseInventoryHelper(const FInputActionValue &Value)
{
    CanOpenInventory = true;
    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Test"));
}


// Called every frame
void AMainCharacter::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    UEnhancedInputComponent *EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
    // Setting up Player Input Action Mappings
    if (EnhancedInputComponent)
    {
        // Player Move
        EnhancedInputComponent->BindAction(InputActionMove, ETriggerEvent::Triggered, this, &AMainCharacter::MoveAction);

        // Player Look Around
        EnhancedInputComponent->BindAction(InputActionLookAround, ETriggerEvent::Triggered, this, &AMainCharacter::LookAroundAction);

        // Player Jump
        EnhancedInputComponent->BindAction(InputActionJump, ETriggerEvent::Triggered, this, &AMainCharacter::JumpAction);

        // Player Light Attack
        EnhancedInputComponent->BindAction(InputActionLightAttack, ETriggerEvent::Triggered, this, &AMainCharacter::LightAttackAction);

        // Player Heavy Attack
        EnhancedInputComponent->BindAction(InputActionHeavyAttack, ETriggerEvent::Triggered, this, &AMainCharacter::HeavyAttackAction);

        // Player Ability Keys
        EnhancedInputComponent->BindAction(InputActionAbilityKey, ETriggerEvent::Triggered, this, &AMainCharacter::AbilityKeyAction);

        // Player Ability Scroll Functions
        EnhancedInputComponent->BindAction(InputActionScrollAbility, ETriggerEvent::Triggered, this, &AMainCharacter::AbilityScrollAction);

        // Player Open or Close Inventory keys
        EnhancedInputComponent->BindAction(InputActionOpenCloseInventory, ETriggerEvent::Triggered, this, &AMainCharacter::OpenCloseInventory);

        // Player Open or Close Inventory keys
        EnhancedInputComponent->BindAction(InputActionOpenCloseInventoryHelper, ETriggerEvent::Triggered, this, &AMainCharacter::OpenCloseInventoryHelper);
    }
}
