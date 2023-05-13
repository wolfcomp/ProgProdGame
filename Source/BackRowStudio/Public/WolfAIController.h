// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "CoreMinimal.h"
#include "WolfAIController.generated.h"

// helpful tutorial: https://www.youtube.com/watch?v=DwjehZh5YQ0&t=119s
// also this other helpful tutorial: https://sologamedevblog.com/tutorials/unreal-perception-c-friend-or-enemy/
// The other controllers need to inherit from IGenericTeamAgentInterface and set their team id. In this example I take the PlayerController

/**
 * wolf ai controller
 */
UCLASS()
class BACKROWSTUDIO_API AWolfAIController : public AAIController
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

private:
    class AWolf *controlledWolf;
    class UNavigationSystemV1 *navArea;
    FVector randomLocation = FVector();

    bool moveToPlayer;
    bool validPlayerPawn;


    //bool PlayerInAttackRange() const;
    //bool IsPointReachable(FVector point) const;
    //void StartChasingPlayer();
    //void AttackPlayer() const;
    //void GenerateRandomSearchLocation();
    //void SearchForPlayer();
    //void OnActiveFinishedMove();

public:
    AWolfAIController();

    int CurrentPatrolPointIndex = 0;
    float PlayerMoveTimeTilNextCheck = 0;
    bool CanMove;
    TArray<FVector> PatrolPoints;

    UPROPERTY(EditAnywhere)
    bool IsInitialized = true;

    UPROPERTY(VisibleAnywhere, Category = AI)
    TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent = nullptr;
    TObjectPtr<class UAISenseConfig_Sight> AISenseConfigSight = nullptr;
    TObjectPtr<class UAISenseConfig_Hearing> AISenseConfigHearing = nullptr;

    void MoveToPlayer();
    void Patrol();
    virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor &other) const override;

    virtual void OnMoveCompleted(FAIRequestID request_id, const FPathFollowingResult &result) override;

    UFUNCTION()
    void OnTargetPerceptionUpdatedDelegate(AActor *actor, FAIStimulus stimulus);
};
