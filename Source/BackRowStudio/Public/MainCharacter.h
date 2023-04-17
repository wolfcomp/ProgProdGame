// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

struct FInputActionValue;

UCLASS()
class BACKROWSTUDIO_API AMainCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    AMainCharacter();

    // |Camera| Spring Arm Component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    class USpringArmComponent *SpringArmComponent;

    // |Camera| Camera Component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    class UCameraComponent *CameraComponent;

    // |Input| Mapping Context Component
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    class UInputMappingContext *MappingContextComponent;

    /**
     * Input Actions
     */
    // |Input Action| Move
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Input Action")
    class UInputAction *InputActionMove;

    // |Input Action| Look Around
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Input Action")
    class UInputAction *InputActionLookAround;

    // |Input Action| Jump
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Input Action")
    class UInputAction *InputActionJump;
    
    // |Input Action| Jump
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Input Action")
    class UInputAction *InputActionLightAttack;
    
    // |Input Action| Jump
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Input Action")
    class UInputAction *InputActionHeavyAttack;
    
    // |Input Action| Jump
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Input Action")
    class UInputAction *InputActionAbilityKey;

    // |Input Action| Jump
    UPROPERTY(EditAnywhere, Category = "Spells | Cold Enhancement")
    class ISpellActor *ColdEnhancement;


protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    /**
     * Action Input Functions
     */
    // Player Move Function
    void MoveAction(const FInputActionValue &Value);

    // Player Look Around Function
    void LookAroundAction(const FInputActionValue &Value);

    // Player Jump Function
    void JumpAction(const FInputActionValue &Value);

    // Player Light Attack Function
    void LightAttackAction(const FInputActionValue &Value);

    // Player Heavy Attack Function
    void HeavyAttackAction(const FInputActionValue &Value);

    // Player Ability Functions
    void AbilityKeyAction(const FInputActionValue &Value);


public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

private:
    // Movement Component
	//UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	//TObjectPtr<UCharacterMovementComponent> CharacterMovement;
};
