// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Wolf.generated.h"

//https://awesometuts.com/blog/unreal-engine-enemy-ai/
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
	bool CanAttackPlayer;

	float CurrentPatrolPoint = 0;

	UPROPERTY(BlueprintReadWrite)
	bool CanDealDamage;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	class AMainCharacter* PlayerRef;

	UPROPERTY(EditAnywhere)
	class AWolfAIController* WolfAIController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USplineComponent* PatrolPath;

	//UPROPERTY(EditAnywhere)
	//class UBlackboardComponent* WolfAiBlackboard;

	//UPROPERTY(EditAnywhere)
	//class UBehaviorTreeComponent* WolfAiBehaviorTree;

	UPROPERTY(EditAnywhere)
	class USphereComponent* PlayerAttackCollisionDetection;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* AttackHitBox;


	UPROPERTY(EditAnywhere)
	class UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere)
	class UAnimInstance* AnimInstance;

	void OnMoveCompleted(struct FAIRequestID RequestID, const struct FPathFollowingResult& Result);
	void OnAttackHitBoxBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION(BlueprintCallable)
	void AttackAnimationEnded();

	UFUNCTION()
	void TryAttack(AActor* actorToAttack);
};
