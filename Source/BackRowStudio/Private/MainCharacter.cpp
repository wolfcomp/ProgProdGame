// Fill out your copyright notice in the Description page of Project Settings.


#include "BackRowStudio/Public/MainCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

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

void AMainCharacter::AbilityKeyAction(const FInputActionValue &Value) { static_cast<int>(Value.Get<float>()); }


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
    }
}
