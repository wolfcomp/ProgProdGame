// Fill out your copyright notice in the Description page of Project Settings.


#include "BackRowStudio/Public/MainCharacter.h"
#include "BaseSpellActor.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Camera/CameraComponent.h"
#include "CheckpointActor.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Components/SphereComponent.h"
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

void AMainCharacter::UnsetAnimationFlag(ECharacterAnimationState flag) { AnimationState &= ~static_cast<uint8>(flag); }

bool AMainCharacter::CheckAnimationFlag(ECharacterAnimationState flag) { return (AnimationState & static_cast<uint8>(flag)) == static_cast<uint8>(flag); }

AMainCharacter::AMainCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->TargetArmLength = 800.f;
    SpringArmComponent->SetWorldRotation((FRotator(-60.f, 0.f, 0.f)));
    SpringArmComponent->bUsePawnControlRotation = true;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    CameraComponent->SetupAttachment(SpringArmComponent);
    CameraComponent->SetFieldOfView(90);

    const auto characterMovementComponent = GetCharacterMovement();
    characterMovementComponent->MaxAcceleration = 10000.f;
    characterMovementComponent->BrakingFrictionFactor = 1000.f;
    characterMovementComponent->MaxWalkSpeed = 800.f;
    AutoPossessPlayer = EAutoReceiveInput::Player0;

    SpellEnenhancements = CreateDefaultSubobject<ABaseSpellActor>(TEXT("ArcaneEnhancement"));
    SpellEnenhancements->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

    MiniMapSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Minimap SpringArm"));
    MiniMapSpringArm->SetupAttachment(GetRootComponent());
    MiniMapSpringArm->TargetArmLength = 900.f;
    MiniMapSpringArm->SetWorldRotation((FRotator(-90.f, 0.f, 0.f)));
    MiniMapSpringArm->bInheritPitch = 0;
    MiniMapSpringArm->bInheritRoll = 0;
    MiniMapSpringArm->bInheritYaw = 0;

    MinimapCam = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("MiniMapCamera"));
    MinimapCam->SetupAttachment(MiniMapSpringArm);
    MinimapCam->ProjectionType = ECameraProjectionMode::Orthographic;
    MinimapCam->OrthoWidth = 2500.f;

    MyInv = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory Component"));
}

void AMainCharacter::BeginPlay()
{
    Super::BeginPlay();

    AnimationAttackTimer = 0;
    AnimationAttackedTimer = 0;
    AnimationPickupTimer = 0;

    AnimationState = static_cast<uint8>(ECharacterAnimationState::Idle);

    OpenOrClosePause = true;

    GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMainCharacter::OnOverlapBegin);
    GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AMainCharacter::OnOverlapEnd);

    if (const auto *controller = Cast<APlayerController>(Controller))
    {
        if (auto *inputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(controller->GetLocalPlayer()))
        {
            inputSystem->AddMappingContext(MappingContextComponent, 0);
        }
    }

    if (MiniMapWidgetTemplate)
    {
        MinimapWidget = CreateWidget<UMinimapWidget>(GetWorld(), MiniMapWidgetTemplate, FName("Minimap"));
        MinimapWidget->AddToViewport();
    }
    if (MyHealthWidget)
    {
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
        PauseMenu = CreateWidget<UPauseWidget>(GetWorld(), MyPauseMenu, FName("Pause Widget"));
        PauseMenu->PC = PC;
        PauseMenu->AddToViewport();
        PauseMenu->SetVisibility(ESlateVisibility::Collapsed);
    }

    if (MyPauseMenu->IsValidLowLevel())
    {
        InvWidget = CreateWidget<UInventoryWidget>(GetWorld(), MyInvWidget, FName("Inventory Widget"));
        InvWidget->Inventory = MyInv;
        InvWidget->AddToViewport();
        InvWidget->SetVisibility(ESlateVisibility::Collapsed);
    }
}

void AMainCharacter::MoveAction(const FInputActionValue &value)
{
    const auto movementVector = value.Get<FVector2D>();

    if (GetController())
    {
        const auto rotation = Controller->GetControlRotation();
        const FRotator yawRotation(0.f, rotation.Yaw, 0.f);

        const FVector forwardDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(forwardDirection, movementVector.Y);

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

void AMainCharacter::JumpAction(const FInputActionValue &value)
{
    AnimationState |= static_cast<uint8>(ECharacterAnimationState::Jumping);
    Super::Jump();
}

void AMainCharacter::LightAttackAction(const FInputActionValue &value)
{
    if (!MyInv->Spells[SelectedSpell].Item)
    {
        return;
    }

    if (CanJump() && SpellEnenhancements)
    {
        AnimationState |= static_cast<uint8>(ECharacterAnimationState::Attack);
        SpellEnenhancements->CastSpell(GetActorLocation(), GetActorRotation(), GetWorld(), GetRootComponent(), false);
    }
}

void AMainCharacter::HeavyAttackAction(const FInputActionValue &value)
{
    if (!MyInv->Spells[SelectedSpell].Item)
    {
        return;
    }

    if (CanJump())
    {
        AnimationState |= static_cast<uint8>(ECharacterAnimationState::Attack);
        if (SpellEnenhancements->Spell->Heavy.IsGroundSpell)
        {
            SpellEnenhancements->CastSpell(GetActorLocation() - FVector(0, 0, GroundSpellLocationOffset), GetActorRotation(), GetWorld(), GetRootComponent(), true);
        }
        else
        {
            SpellEnenhancements->CastSpell(GetActorLocation(), GetActorRotation(), GetWorld(), GetRootComponent(), true);
        }
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
    {
        SelectedSpell = 3;
    }

    if (SelectedSpell > 3)
    {
        SelectedSpell = 0;
    }

    SetSpell();
}

void AMainCharacter::SetSpell()
{
    auto spellItem = MyInv->Spells[SelectedSpell].Item;
    if (!spellItem)
    {
        return;
    }

    auto spell = spellItem->Spell;
    if (!spell)
    {
        return;
    }

    SpellEnenhancements->Spell = spell;
    SpellEnenhancements->SetData();
}

void AMainCharacter::OpenCloseInventory(const FInputActionValue &value)
{
    if (InvWidget && PC)
    {
        if (OpenInventory)
        {
            InvWidget->UpdateInventory();
            UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PC, InvWidget);
            PC->SetShowMouseCursor(true);
            PC->SetPause(true);
            InvWidget->SetVisibility(ESlateVisibility::Visible);
            OpenInventory = false;
            return;
        }

        UWidgetBlueprintLibrary::SetInputMode_GameOnly(PC);
        PC->SetShowMouseCursor(false);
        PC->SetPause(false);
        InvWidget->SetVisibility(ESlateVisibility::Collapsed);
        OpenInventory = true;
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

void AMainCharacter::DebugAction(const FInputActionValue &value)
{
    RespawnLocation->RespawnOthers();
    RespawnLocation->RespawnPlayer(this);
}

void AMainCharacter::AttachSpellComponents(FName socket_name) { SpellEnenhancements->AttachToComponent(GetRootComponent(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), FName(socket_name)); }

bool AMainCharacter::ShouldNotifyLanded(const FHitResult &Hit)
{
    UnsetAnimationFlag(ECharacterAnimationState::Jumping);
    return Super::ShouldNotifyLanded(Hit);
}

void AMainCharacter::OnOverlapBegin(UPrimitiveComponent *overlapped_component, AActor *other_actor, UPrimitiveComponent *other_component, int other_index, bool from_sweep, const FHitResult &sweep_result)
{
    if (const auto item = Cast<AItemActor>(other_actor))
    {
        if (item->Item != nullptr && !item->IsPickedUp)
        {
            AnimationState |= static_cast<uint8>(ECharacterAnimationState::Pickup);
            if (item->Item->Spell == nullptr)
            {
                if (MyInv->AddItem(FSlotStruct(item->Item, 1)))
                {
                    UGameplayStatics::PlaySound2D(this, PickupSound);
                }
            }
            else if (MyInv->AddSpell(FSlotStruct(item->Item, 1)))
            {
                SetSpell();
                UGameplayStatics::PlaySound2D(this, PickupSound);
            }

            item->IsPickedUp = true;
            item->Mesh->SetVisibility(false);
            item->SphereCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        }
    }
    if (const auto wolf = Cast<AWolf>(other_actor))
    {
        beingAttacked = true;
        attackingPower += wolf->AttackPower;
    }
    if (const auto enemy = Cast<AEnemy>(other_actor))
    {
        Health -= enemy->AttackPower;
        AnimationState |= static_cast<uint8>(ECharacterAnimationState::Attacked);
        auto distance = GetActorLocation() - enemy->GetActorLocation();
        distance *= FVector(1, 1, 0);
        distance.Normalize();
        distance.Z = .45;
        distance *= enemy->PushForce;
        LaunchCharacter(distance, true, true);
    }
}

void AMainCharacter::OnOverlapEnd(UPrimitiveComponent *primitive_component, AActor *other_actor, UPrimitiveComponent *other_component, int i)
{
    if (const auto wolf = Cast<AWolf>(other_actor))
    {
        beingAttacked = false;
        attackingPower -= wolf->AttackPower;
    }
    if (attackingPower == 0)
    {
        attackTimer = 0;
    }
}

void AMainCharacter::Tick(float delta_time)
{
    Super::Tick(delta_time);
    if (beingAttacked)
    {
        attackTimer += delta_time;
        if (attackTimer > AttackedTimeCooldown)
        {
            AnimationState |= static_cast<uint8>(ECharacterAnimationState::Attacked);
            Health -= attackingPower;
            attackTimer = 0;
        }
    }
    if (CheckAnimationFlag(ECharacterAnimationState::Attacked))
    {
        AnimationAttackedTimer += delta_time;
    }
    if (AnimationAttackedTimer >= AnimationAttackedLength)
    {
        UnsetAnimationFlag(ECharacterAnimationState::Attacked);
        AnimationAttackedTimer = 0;
    }
    if (CheckAnimationFlag(ECharacterAnimationState::Attack))
    {
        AnimationAttackTimer += delta_time;
    }
    if (AnimationAttackTimer >= AnimationAttackLength)
    {
        UnsetAnimationFlag(ECharacterAnimationState::Attack);
        AnimationAttackTimer = 0;
    }
    if (CheckAnimationFlag(ECharacterAnimationState::Pickup))
    {
        AnimationPickupTimer += delta_time;
    }
    if (AnimationPickupTimer >= AnimationPickupLength)
    {
        UnsetAnimationFlag(ECharacterAnimationState::Pickup);
        AnimationPickupTimer = 0;
    }
    if (RespawnLocation && Health < 0)
    {
        AnimationState = static_cast<uint8>(ECharacterAnimationState::Death);
        if (beingAttacked)
        {
            RespawnLocation->RespawnOthers();
            beingAttacked = false;
            GetController()->SetIgnoreMoveInput(true);
            GetController()->SetIgnoreLookInput(true);
        }
        respawnTimer += delta_time;
    }
    if (RespawnLocation && respawnTimer > 1)
    {
        AnimationState = static_cast<uint8>(ECharacterAnimationState::Idle);
        GetController()->ResetIgnoreInputFlags();
        RespawnLocation->RespawnPlayer(this);
        attackingPower = 0;
        respawnTimer = 0;
    }
}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent *input_component)
{
    Super::SetupPlayerInputComponent(input_component);

    if (auto *enhancedInputComponent = CastChecked<UEnhancedInputComponent>(input_component))
    {
        enhancedInputComponent->BindAction(InputActionMove, ETriggerEvent::Triggered, this, &AMainCharacter::MoveAction);

        enhancedInputComponent->BindAction(InputActionLookAround, ETriggerEvent::Triggered, this, &AMainCharacter::LookAroundAction);

        enhancedInputComponent->BindAction(InputActionJump, ETriggerEvent::Triggered, this, &AMainCharacter::JumpAction);

        enhancedInputComponent->BindAction(InputActionLightAttack, ETriggerEvent::Triggered, this, &AMainCharacter::LightAttackAction);

        enhancedInputComponent->BindAction(InputActionHeavyAttack, ETriggerEvent::Triggered, this, &AMainCharacter::HeavyAttackAction);

        enhancedInputComponent->BindAction(InputActionAbilityKey, ETriggerEvent::Triggered, this, &AMainCharacter::AbilityKeyAction);

        enhancedInputComponent->BindAction(InputActionScrollAbility, ETriggerEvent::Triggered, this, &AMainCharacter::AbilityScrollAction);

        enhancedInputComponent->BindAction(InputActionOpenCloseInventory, ETriggerEvent::Started, this, &AMainCharacter::OpenCloseInventory);

        enhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &AMainCharacter::OpenClosePauseMenu);

        enhancedInputComponent->BindAction(DebugActionKey, ETriggerEvent::Started, this, &AMainCharacter::DebugAction);
    }
}

void AMainCharacter::SetCheckpoint(ACheckpointActor *checkpoint) { RespawnLocation = checkpoint; }
