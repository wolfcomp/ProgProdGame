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

    NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
    bMoveToPlayer = false;

    if (AWolf *localControlledWolf = Cast<AWolf>(this->GetCharacter()); this->GetCharacter()->IsValidLowLevel() && localControlledWolf->IsValidLowLevel())
    {
        controlledWolf = localControlledWolf;
        bValidPlayerPawn = true;
        for (int i = 0; i < controlledWolf->PatrolPath->GetNumberOfSplinePoints(); ++i)
        {
            if (controlledWolf->PatrolPath->GetWorldLocationAtSplinePoint(i) != FVector(0, 0, 0))
            {
                patrolPoints.Add(controlledWolf->PatrolPath->GetWorldLocationAtSplinePoint(i));
            }
        }
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Dafuq am i Controlling? -WolfAiController"));
    }

    if (IsInitialized)
    {
        if (controlledWolf->PatrolPath->IsValidLowLevel() && controlledWolf->PatrolPath->GetNumberOfSplinePoints() > 0)
        {
            Patrol();
        }
    }
    AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ThisClass::OnTargetPerceptionUpdated_Delegate);
}

void AWolfAIController::Tick(float DeltaSeconds) { Super::Tick(DeltaSeconds); }

void AWolfAIController::MoveToPlayer()
{
    if (playerMoveTimeTilNextCheck <= GetWorld()->TimeSeconds)
    {
        if (bMoveToPlayer == true)
        {
            const FAIMoveRequest nextPatrolPoint = FAIMoveRequest(controlledWolf->PlayerRef->GetNavAgentLocation());
            if (const double distance = FVector::Dist(controlledWolf->GetNavAgentLocation(), controlledWolf->PlayerRef->GetNavAgentLocation());
            nextPatrolPoint.IsValid() && distance > 10)
            {
                MoveToActor(controlledWolf->PlayerRef);
            }
            else if (distance <= controlledWolf->PlayerAttackCollisionDetectionRadius)
            {
                controlledWolf->TryAttack(controlledWolf->PlayerRef);
            }
            else
            {
                controlledWolf->TryStoppingAttack();
            }
        }
        playerMoveTimeTilNextCheck = GetWorld()->TimeSeconds + 1;
    }
}

void AWolfAIController::Patrol()
{
    if (PatrolMoveTimeTilNextCheck <= GetWorld()->TimeSeconds)
    {
        FAIMoveRequest nextPatrolPoint = FAIMoveRequest(patrolPoints[CurrentPatrolPointIndex]);
        if (nextPatrolPoint.IsValid())
        {
            MoveTo(nextPatrolPoint);
        }
        if (CurrentPatrolPointIndex + 1 < patrolPoints.Num())
        {
            CurrentPatrolPointIndex++;
        }
        else
        {
            CurrentPatrolPointIndex = 0;
        }
        playerMoveTimeTilNextCheck = GetWorld()->TimeSeconds + 1;
    }
}

void AWolfAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult &Result)
{
    if (Result.IsSuccess() && !Result.IsInterrupted())
    {
        if (bMoveToPlayer)
        {
            MoveToPlayer();
        }
        else
        {
            Patrol();
        }
    }
    // Super::OnMoveCompleted(RequestID, Result);
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
        MoveToPlayer();
    }
    switch (Stimulus.Type)
    {
    case 0:
        // react to sight stimulus

    case 1:
        // react to hearing;
    default:
        return;
    }
}

// void AWolfAIController::StartChasingPlayer()
//{
//	IsPatrolling = false;
//	MoveToPlayer();
// }

// bool AWolfAIController::IsPointReachable(FVector point) const
//{
//	FPathFindingQuery A14;
//	FNavLocation a15;
//	NavArea->GetRandomReachablePointInRadius(point, 10, a15);
//	const FPathFindingResult pathResult = NavArea->GetAbstractNavData()->
//	                                               FindPath(this->GetNavAgentPropertiesRef(), A14);
//	if (pathResult.Result != ENavigationQueryResult::Error && pathResult.IsSuccessful() && pathResult.Path.IsValid() &&
//		!pathResult.IsPartial())
//	{
//		return true;
//	}
//	if (!a15.HasNodeRef())
//	{
//		return true;
//	}
//	if (pathResult.Result == ENavigationQueryResult::Error)
//	{
//		//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red,TEXT("1 wolf.cpp 172"));
//		//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red,);
//	}
//	else if (!pathResult.IsSuccessful())
//	{
//		//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red,TEXT("2 wolf.cpp 176"));
//	}
//	else if (!pathResult.Path.IsValid())
//	{
//		//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red,TEXT("3 wolf.cpp 180"));
//	}
//	return false;
// }

// void AWolfAIController::GenerateRandomSearchLocation()
//{
//	if (FNavLocation result; NavArea->GetRandomReachablePointInRadius(GetPawn()->GetActorLocation(), 10000.0f, result))
//	{
//		RandomLocation = result.Location;
//	};
// }

// void AWolfAIController::SearchForPlayer()
//{
//	if (!IsPointReachable(RandomLocation) || RandomLocation == FVector())
//	{
//		GenerateRandomSearchLocation();
//	}
//	MoveToLocation(RandomLocation);
// }

// void AWolfAIController::Reactivate()
//{
//	if (!bIsActive)
//	{
//		bIsActive = true;
//	}
//	OnActiveFinishedMove();
// }
//
// void AWolfAIController::Deactivate()
//{
//	bIsActive = false;
//	if (IsFollowingAPath())
//	{
//		StopMovement();
//	}
// }

// bool AWolfAIController::PlayerInAttackRange() const
//{
//	if (controlledWolf->PlayerRef->IsValidLowLevel() && controlledWolf->IsValidLowLevel())
//	{
//		const float distance = FVector::Dist(controlledWolf->PlayerRef->GetActorLocation(), this->controlledWolf->GetActorLocation());
//		if (distance <= wolfAttackDistance)
//		{
//			return true;
//		}
//	}
//	return false;
// }

// void AWolfAIController::AttackPlayer() const
//{
//	controlledWolf->TryAttack(controlledWolf->PlayerRef);
// }

// not done
// void AWolfAIController::ReturnToPatrol()
//{
//	if (controlledWolf->PatrolPath->IsValidLowLevel())
//	{
//		if (IsFollowingAPath())
//		{
//			StopMovement();
//		}
//		Patrol();
//	}
//}