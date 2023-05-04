// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "CoreMinimal.h"
#include "WolfAIController.generated.h"

// helpful tutorial: https://www.youtube.com/watch?v=DwjehZh5YQ0&t=119s
// also this other helpful tutorial: https://sologamedevblog.com/tutorials/unreal-perception-c-friend-or-enemy/
// The other controllers need to inherit from IGenericTeamAgentInterface and set their team id. In this example I take the PlayerController

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
	class AWolf* controlledWolf;
	class UNavigationSystemV1* NavArea;
	FVector RandomLocation = FVector();

	bool bMoveToPlayer;
	bool bValidPlayerPawn;


	//bool PlayerInAttackRange() const;
	//bool IsPointReachable(FVector point) const;
	//void StartChasingPlayer();
	//void AttackPlayer() const;
	//void GenerateRandomSearchLocation();
	//void SearchForPlayer();
	//void OnActiveFinishedMove();

public:
	UPROPERTY(VisibleAnywhere, Category = AI)
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent = nullptr;
	TObjectPtr<class UAISenseConfig_Sight> AISenseConfigSight = nullptr;
	TObjectPtr<class UAISenseConfig_Hearing> AISenseConfigHearing = nullptr;

	float playerMoveTimeTilNextCheck = 0;
	TArray<FVector> patrolPoints;
	float PatrolMoveTimeTilNextCheck = 0;

	void MoveToPlayer();
	void Patrol();
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

	AWolfAIController();

	UPROPERTY(EditAnywhere)
	bool IsInitialized = true;

	int CurrentPatrolPointIndex;

	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	UFUNCTION()
	void OnTargetPerceptionUpdated_Delegate(AActor* Actor, FAIStimulus Stimulus);
};
