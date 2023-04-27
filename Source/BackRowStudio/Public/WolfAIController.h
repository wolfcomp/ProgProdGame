// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "WolfAIController.generated.h"

//helpful tutorial: https://www.youtube.com/watch?v=DwjehZh5YQ0&t=119s
//also this other helpful tutorial: https://sologamedevblog.com/tutorials/unreal-perception-c-friend-or-enemy/
    //The other controllers need to inherit from IGenericTeamAgentInterface and set their team id. In this example I take the PlayerController

/**
 * 
 */
UCLASS()
class BACKROWSTUDIO_API AWolfAIController : public AAIController
{
	GENERATED_BODY()
protected:
    virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	APawn* PlayerPawn;

	class AWolf* controlledWolf;

	class UNavigationSystemV1* NavArea;

	FVector RandomLocation = FVector();
	TArray<FVector> patrolPoints;

	bool bIsActive;
	bool bMoveToPlayer;
	bool bSearchForPlayer;
	bool bCanAttackPlayer;

	float wolfAttackDistance = 200.0f;
	float currentPatrolPoint = 0;

	void GenerateRandomSearchLocation();
	void SearchForPlayer();

	void MoveToPlayer();
	void StartChasingPlayer();
	bool PlayerInAttackRange() const;
	void AttackPlayer() const;
	void Patrol();

	FTimerHandle SearchTimerHandle;
	FTimerHandle AttackTimerHandle;

public:
	AWolfAIController();

	UPROPERTY(VisibleAnywhere, Category = AI)
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent = nullptr;
	TObjectPtr<class UAISenseConfig_Sight> AISenseConfigSight = nullptr;
	TObjectPtr<class UAISenseConfig_Hearing> AISenseConfigHearing = nullptr;

	UPROPERTY(EditAnywhere)
	bool IsPatrolling = true;

	UPROPERTY(EditAnywhere)
	bool IsInitialized = true;

    virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult &Result) override;
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

    UFUNCTION()
	void OnTargetPerceptionUpdated_Delegate(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION()
	void Reactivate();

	UFUNCTION(BlueprintCallable)
	void ReturnToPatrol();


};
