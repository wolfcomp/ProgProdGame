// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Wolf.generated.h"

// https://awesometuts.com/blog/unreal-engine-enemy-ai/
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
	bool PlayerDetected;
	bool IsAttackingFrame = false;
	float CurrentPatrolPoint = 0;
	float CurrentSpotRadius = 640;
	//bool CanAttackPlayer;
	//UPROPERTY(BlueprintReadWrite)
	//bool CanDealDamage;

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

	//UPROPERTY(EditAnywhere)
	//class USphereComponent* PlayerAttackCollisionDetection;

	//UPROPERTY(EditAnywhere)
	//class USphereComponent* PlayerAutoSpotRadius;

	//UPROPERTY(EditAnywhere)
	//class USphereComponent* PlayerForgetRadius;

	UPROPERTY(EditAnywhere)
	float PlayerAttackCollisionDetectionRadius = 320;

	UPROPERTY(EditAnywhere)
	float PlayerAutoSpotRadius = 640;

	UPROPERTY(EditAnywhere)
	float PlayerForgetRadius = 1280;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* AttackHitBox;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* AttackMontage;

	UFUNCTION()
	void TryAttack(AActor* actorToAttack);

	UFUNCTION(BlueprintCallable)
	void AttackAnimationEnded();

	UFUNCTION(BlueprintCallable)
	void AttackAnimationBegin();

	UFUNCTION(BlueprintCallable)
	void AttackingFramesBegin();

	UFUNCTION(BlueprintCallable)
	void AttackingFramesEnd();
};
