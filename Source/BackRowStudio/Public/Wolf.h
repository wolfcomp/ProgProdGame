// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Wolf.generated.h"

// https://awesometuts.com/blog/unreal-engine-enemy-ai/

UENUM(BlueprintType)
enum WolfAnimationType
{
	Stopped UMETA(DisplayName = "Stopped"),
	Moving UMETA(DisplayName = "Moving"),
	Attacking UMETA(DisplayName = "Attacking"),
};

UCLASS()
class BACKROWSTUDIO_API AWolf : public ADamageActor
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWolf();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY()
	class AMainCharacter* PlayerRef;

	UPROPERTY()
	class AWolfAIController* WolfAIController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USplineComponent* PatrolPath;

	UPROPERTY(EditAnywhere)
	float PlayerAttackCollisionDetectionRadius = 320;

	UPROPERTY(EditAnywhere)
	float PlayerForgetRadius = 1280;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* AttackHitBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<WolfAnimationType> MyAnimationState = WolfAnimationType::Moving;

	UFUNCTION()
	void TryAttack(AActor* actorToAttack);

	UFUNCTION()
	void TryStoppingAttack();
};
