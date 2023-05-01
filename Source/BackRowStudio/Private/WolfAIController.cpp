// Fill out your copyright notice in the Description page of Project Settings.


#include "WolfAIController.h"

#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"

#include "Components/SphereComponent.h"
#include "Components/SplineComponent.h"
#include "MainCharacter.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Wolf.h"

AWolfAIController::AWolfAIController()
{
    AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComponent");
    AISenseConfigSight = CreateDefaultSubobject<UAISenseConfig_Sight>("SenseSight");
    AISenseConfigSight->DetectionByAffiliation.bDetectEnemies = true;
    AISenseConfigSight->DetectionByAffiliation.bDetectFriendlies = false;
    AISenseConfigSight->DetectionByAffiliation.bDetectNeutrals = false;

    AISenseConfigHearing = CreateDefaultSubobject<UAISenseConfig_Hearing>("SenseHearing");
    AISenseConfigHearing->DetectionByAffiliation.bDetectEnemies = true;
    AISenseConfigHearing->DetectionByAffiliation.bDetectFriendlies = false;
    AISenseConfigHearing->DetectionByAffiliation.bDetectNeutrals = false;

    AIPerceptionComponent->ConfigureSense(*AISenseConfigSight);
    AIPerceptionComponent->ConfigureSense(*AISenseConfigHearing);
    AIPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());

    // Team ID For Wolf
    AWolfAIController::SetGenericTeamId(FGenericTeamId(1));
}

void AWolfAIController::BeginPlay()
{
    Super::BeginPlay();

    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if (AWolf *localControlledWolf = Cast<AWolf>(this->GetCharacter()); this->GetCharacter()->IsValidLowLevel() && localControlledWolf)
    {
        controlledWolf = localControlledWolf;
        wolfAttackDistance = controlledWolf->PlayerAttackCollisionDetection->GetScaledSphereRadius();
        for (int i = 0; i < controlledWolf->PatrolPath->GetNumberOfSplinePoints(); ++i)
        {
            patrolPoints.Add(controlledWolf->PatrolPath->GetWorldLocationAtSplinePoint(i));
        }
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Dafuq am i Controlling? -WolfAiController"));
    }

    NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);

    bIsActive = true;
    bSearchForPlayer = true;
    bCanAttackPlayer = true;
    bMoveToPlayer = false;

    if (IsInitialized)
    {
        GenerateRandomSearchLocation();
        if (controlledWolf->PatrolPath->IsValidLowLevel() && controlledWolf->PatrolPath->GetNumberOfSplinePoints() > 0 && IsPatrolling == true)
        {
            IsPatrolling = true;
            bSearchForPlayer = false;
            Patrol();
        }
        else
        {
            SearchForPlayer();
        }
    }

    AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ThisClass::OnTargetPerceptionUpdated_Delegate);
}

void AWolfAIController::Tick(float DeltaSeconds) { Super::Tick(DeltaSeconds); }

void AWolfAIController::GenerateRandomSearchLocation()
{
    FNavLocation result;
    if (NavArea->GetRandomReachablePointInRadius(GetPawn()->GetActorLocation(), 10000.0f, result))
    {
        RandomLocation = result.Location;
    };
}

void AWolfAIController::SearchForPlayer() { MoveToLocation(RandomLocation); }

void AWolfAIController::MoveToPlayer()
{
    if (PlayerPawn->IsValidLowLevel())
    {
        if (IsPointReachable(PlayerPawn->GetActorLocation()))
        {
            if (PlayerInAttackRange())
            {
                if (bCanAttackPlayer == true)
                {
                    GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("attacking player"));
                    AttackPlayer();
                }
            }
            else if (const float distance = FVector::Dist(PlayerPawn->GetActorLocation(), this->controlledWolf->GetActorLocation()); distance > 300 /*&& IsPointReachable(PlayerPawn->GetNavAgentLocation())*/)
            {
                MoveToActor(PlayerPawn);
                bSearchForPlayer = false;
                bMoveToPlayer = true;
            }
            else if (!bCanAttackPlayer)
            {
                bMoveToPlayer = false;
            }
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("can't reach player"));
        }
    }
}

void AWolfAIController::StartChasingPlayer()
{
    IsPatrolling = false;
    MoveToPlayer();
}

bool AWolfAIController::PlayerInAttackRange() const
{
    if (PlayerPawn->IsValidLowLevel() && controlledWolf->IsValidLowLevel())
    {
        const float distance = FVector::Dist(PlayerPawn->GetActorLocation(), this->controlledWolf->GetActorLocation());
        if (distance <= wolfAttackDistance)
        {
            return true;
        }
    }
    return false;
}

bool AWolfAIController::IsPointReachable(FVector point) const
{
    //const ANavigationData* a14 = NavArea->AbstractNavData->FindPath(this->GetNavAgentPropertiesRef(),a1);

    //const FPathFindingQuery a1 = FPathFindingQuery(this, a14, controlledWolf->GetActorLocation(), point);
    //FPathFindingResult a15 = NavArea->AbstractNavData->FindPath(this->GetNavAgentPropertiesRef(),FPathFindingQuery());
    if (const FPathFindingResult pathResult = NavArea->AbstractNavData->FindPath(this->GetNavAgentPropertiesRef(), FPathFindingQuery(this, *NavArea->NavDataSet.GetData()->Get(), GetNavAgentLocation(), point)); pathResult.Result != ENavigationQueryResult::Error)
    {
        if (pathResult.IsSuccessful() && pathResult.Path.IsValid())
        {
            return true;
        }
    }
    return false;
}

void AWolfAIController::AttackPlayer() const
{
    controlledWolf->TryAttack(PlayerPawn);
}

void AWolfAIController::Patrol()
{
    // GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red,TEXT("2"));
    DrawDebugSphere(GetWorld(), patrolPoints[currentPatrolPoint], 200, 16, FColor::Red, true, 100000);
    if (!controlledWolf->IsValidLowLevel()) { return; }
    //if (!IsPointReachable(PlayerPawn->GetNavAgentLocation())) { return; }
    if (IsPatrolling && controlledWolf->PatrolPath->IsValidLowLevel() && controlledWolf->PatrolPath->IsClosedLoop())
    {
        MoveToLocation(patrolPoints[currentPatrolPoint]);
        if (patrolPoints.IsValidIndex(0))
        {
            if (currentPatrolPoint + 1 < patrolPoints.Num())
            {
                GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("1"));
                currentPatrolPoint++;
            }
            else
            {
                GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("2"));
                currentPatrolPoint = 0;
            }
        }
    }
}

// EPathFollowingResultDetails should be used cuz this version of the parameters below is depricated
void AWolfAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult &Result)
{
    if (controlledWolf)
    {

        controlledWolf->OnMoveCompleted(RequestID, Result);
    }
    Super::OnMoveCompleted(RequestID, Result);
    if (IsPatrolling && !bMoveToPlayer)
    {
        Patrol();
    }
    else if (bMoveToPlayer)
    {
        StartChasingPlayer();
    }
    else if (bSearchForPlayer)
    {
        GenerateRandomSearchLocation();
        SearchForPlayer();
    }
    else
    {
        bIsActive = false;
    }
}

ETeamAttitude::Type AWolfAIController::GetTeamAttitudeTowards(const AActor &Other) const
{
    if (APawn const *OtherPawn = Cast<APawn>(&Other))
    {
        if (auto const TeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController()))
        {
            if (TeamAgent->GetGenericTeamId() == FGenericTeamId(0) || TeamAgent->GetGenericTeamId() == FGenericTeamId(1))
            {
                return ETeamAttitude::Friendly;
            }
            return ETeamAttitude::Hostile;
        }
    }
    return ETeamAttitude::Neutral;
}

void AWolfAIController::OnTargetPerceptionUpdated_Delegate(AActor *Actor, FAIStimulus Stimulus)
{
    if (GetTeamAttitudeTowards(*Actor) == ETeamAttitude::Hostile)
    {
        IsPatrolling = false;
        StartChasingPlayer();
    }
    switch (Stimulus.Type)
    {
    case 0:
    // react to sight stimulus
    // GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("react to sight stimulus"));
    case 1:
        // react to hearing;
        // GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("react to hearing"));
    default:
        return;
    }
}

void AWolfAIController::Reactivate()
{
    if (!bIsActive)
    {
        bIsActive = true;
        GenerateRandomSearchLocation();
        SearchForPlayer();
    }
}

// not done
void AWolfAIController::ReturnToPatrol()
{
    if (controlledWolf->PatrolPath->IsValidLowLevel())
    {
        FVector closestLocation = controlledWolf->PatrolPath->FindLocationClosestToWorldLocation(controlledWolf->GetActorLocation(), ESplineCoordinateSpace::Type::World);

        float distanceToPoint;
        controlledWolf->CurrentPatrolPoint = controlledWolf->PatrolPath->GetSplinePointsPosition().InaccurateFindNearest(closestLocation, distanceToPoint);
        MoveToLocation(closestLocation);
        IsPatrolling = true;
    }
}
