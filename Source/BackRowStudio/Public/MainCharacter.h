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
	class USpringArmComponent* SpringArmComponent;

	// |Camera| Camera Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* CameraComponent;

	// |Input| Mapping Context Component
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* MappingContextComponent;

	/**
	 * Input Actions
	 */
	// |Input Action| Move
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Input Action")
	class UInputAction* InputActionMove;

	// |Input Action| Look Around
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Input Action")
	class UInputAction* InputActionLookAround;

    // |Input Action| Jump
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input | Input Action")
	class UInputAction* InputActionJump;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**
	 * Action Input Functions
	 */
	//Player Move Function
	void MoveAction(const FInputActionValue& Value);
   
	//Player Look Around Function
	void LookAroundAction(const FInputActionValue& Value);

    //Player Look Around Function
	void JumpAction(const FInputActionValue& Value);



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
};
