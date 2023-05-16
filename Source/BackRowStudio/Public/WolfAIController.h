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
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess))
    class AWolf *controlledWolf;
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess))
    class UNavigationSystemV1 *navArea;

    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess))
    bool moveToPlayer;

public:
    AWolfAIController();

    UPROPERTY(EditAnywhere)
    int CurrentPatrolPointIndex = 0;
    UPROPERTY(EditAnywhere)
    float PlayerMoveTimeTilNextCheck = 0;
    UPROPERTY(EditAnywhere)
    bool CanMove = true;
    UPROPERTY(EditAnywhere)
    TArray<FVector> PatrolPoints;

    UPROPERTY(EditAnywhere)
    bool IsInitialized = true;

    UPROPERTY(VisibleAnywhere, Category = AI)
    TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent = nullptr;
    TObjectPtr<class UAISenseConfig_Sight> AISenseConfigSight = nullptr;
    TObjectPtr<class UAISenseConfig_Hearing> AISenseConfigHearing = nullptr;

    UFUNCTION(CallInEditor)
    void MoveToPlayer();
    UFUNCTION(CallInEditor)
    void Patrol();
    virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor &other) const override;

    virtual void OnMoveCompleted(FAIRequestID request_id, const FPathFollowingResult &result) override;
    virtual void OnPossess(APawn *InPawn) override;

    UFUNCTION()
    void OnTargetPerceptionUpdatedDelegate(AActor *actor, FAIStimulus stimulus);
};
