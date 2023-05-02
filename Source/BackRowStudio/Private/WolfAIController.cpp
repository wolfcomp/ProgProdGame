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
	//AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComponent");
	//AISenseConfigSight = CreateDefaultSubobject<UAISenseConfig_Sight>("SenseSight");
	//AISenseConfigSight->DetectionByAffiliation.bDetectEnemies = true;
	//AISenseConfigSight->DetectionByAffiliation.bDetectFriendlies = false;
	//AISenseConfigSight->DetectionByAffiliation.bDetectNeutrals = false;

	//AISenseConfigHearing = CreateDefaultSubobject<UAISenseConfig_Hearing>("SenseHearing");
	//AISenseConfigHearing->DetectionByAffiliation.bDetectEnemies = true;
	//AISenseConfigHearing->DetectionByAffiliation.bDetectFriendlies = false;
	//AISenseConfigHearing->DetectionByAffiliation.bDetectNeutrals = false;

	//AIPerceptionComponent->ConfigureSense(*AISenseConfigSight);
	//AIPerceptionComponent->ConfigureSense(*AISenseConfigHearing);
	//AIPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());

	//// Team ID For Wolf
	//AWolfAIController::SetGenericTeamId(FGenericTeamId(1));
}

void AWolfAIController::BeginPlay()
{
	Super::BeginPlay();

	NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
	bIsActive = true;
	bMoveToPlayer = false;
	bSearchForPlayer = true;

	if (AWolf* localControlledWolf = Cast<AWolf>(this->GetCharacter()); this->GetCharacter()->IsValidLowLevel() &&
		localControlledWolf->IsValidLowLevel())
	{
		controlledWolf = localControlledWolf;
		bValidPlayerPawn = true;
		for (int i = 0; i < controlledWolf->PatrolPath->GetNumberOfSplinePoints(); ++i)
		{
			patrolPoints.Add(controlledWolf->PatrolPath->GetWorldLocationAtSplinePoint(i));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Dafuq am i Controlling? -WolfAiController"));
	}

	if (IsInitialized)
	{
		if (controlledWolf->PatrolPath->IsValidLowLevel() && controlledWolf->PatrolPath->GetNumberOfSplinePoints() > 0
			&& IsPatrolling == true)
		{
			bSearchForPlayer = false;
			Patrol();
		}
		else
		{
			SearchForPlayer();
		}
	}
	//AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ThisClass::OnTargetPerceptionUpdated_Delegate);
}

void AWolfAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (controlledWolf->PlayerDetected == true && bMoveToPlayer == false && bIsActive && bValidPlayerPawn)
	{
		if (IsFollowingAPath())
		{
			StopMovement();
		}
		bMoveToPlayer = true;
		MoveToPlayer();
	}
}

void AWolfAIController::GenerateRandomSearchLocation()
{
	if (FNavLocation result; NavArea->GetRandomReachablePointInRadius(GetPawn()->GetActorLocation(), 10000.0f, result))
	{
		RandomLocation = result.Location;
	};
}

void AWolfAIController::SearchForPlayer()
{
	if (!IsPointReachable(RandomLocation) || RandomLocation == FVector())
	{
		GenerateRandomSearchLocation();
	}
	MoveToLocation(RandomLocation);
}

void AWolfAIController::OnActiveFinishedMove()
{
	if (IsPatrolling)
	{
		Patrol();
	}
	else if (bMoveToPlayer)
	{
		MoveToPlayer();
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

void AWolfAIController::MoveToPlayer()
{
	if (IsPointReachable(controlledWolf->PlayerRef->GetActorLocation()))
	{
		bSearchForPlayer = false;
		bMoveToPlayer = true;
		IsPatrolling = false;
		MoveToLocation(controlledWolf->PlayerRef->GetActorLocation());
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red,TEXT("Can't reach player"));
		bIsActive = false;
	}
}

bool AWolfAIController::IsPointReachable(FVector point) const
{
	const FPathFindingQuery a14 = FPathFindingQuery(this, *NavArea->NavDataSet.GetData()->Get(), GetNavAgentLocation(),
	                                                point);
	if (const FPathFindingResult pathResult = NavArea->AbstractNavData->FindPath(this->GetNavAgentPropertiesRef(), a14);
		pathResult.Result != ENavigationQueryResult::Error && pathResult.IsSuccessful() && pathResult.Path.IsValid())
	{
		return true;
	}
	return false;
}

void AWolfAIController::Patrol()
{
	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("2"));
	DrawDebugSphere(GetWorld(), patrolPoints[controlledWolf->CurrentPatrolPoint], 200, 16, FColor::Red, true, 100000);
	if (IsPatrolling && controlledWolf->PatrolPath->IsValidLowLevel() && controlledWolf->PatrolPath->IsClosedLoop() &&
		controlledWolf->IsValidLowLevel() && patrolPoints.IsValidIndex(0))
	{
		if (controlledWolf->CurrentPatrolPoint + 1 < patrolPoints.Num())
		{
			controlledWolf->CurrentPatrolPoint++;
		}
		else
		{
			controlledWolf->CurrentPatrolPoint = 0;
		}
		if (IsPointReachable(patrolPoints[controlledWolf->CurrentPatrolPoint]))
		{
			MoveToLocation(patrolPoints[controlledWolf->CurrentPatrolPoint]);
			return;
		}
	}
	bIsActive = false;
}

void AWolfAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	if (bIsActive)
	{
		OnActiveFinishedMove();
	}
}

void AWolfAIController::Reactivate()
{
	if (!bIsActive)
	{
		bIsActive = true;
	}
	OnActiveFinishedMove();
}

void AWolfAIController::Deactivate()
{
	bIsActive = false;
	if (IsFollowingAPath())
	{
		StopMovement();
	}
}

//void AWolfAIController::StartChasingPlayer()
//{
//	IsPatrolling = false;
//	MoveToPlayer();
//}

//bool AWolfAIController::PlayerInAttackRange() const
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
//}

//void AWolfAIController::AttackPlayer() const
//{
//	controlledWolf->TryAttack(controlledWolf->PlayerRef);
//}

//ETeamAttitude::Type AWolfAIController::GetTeamAttitudeTowards(const AActor &Other) const
//{
//    if (APawn const *OtherPawn = Cast<APawn>(&Other))
//    {
//        if (auto const TeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController()))
//        {
//            if (TeamAgent->GetGenericTeamId() == FGenericTeamId(0) || TeamAgent->GetGenericTeamId() == FGenericTeamId(1))
//            {
//                return ETeamAttitude::Friendly;
//            }
//            return ETeamAttitude::Hostile;
//        }
//    }
//    return ETeamAttitude::Neutral;
//}

//void AWolfAIController::OnTargetPerceptionUpdated_Delegate(AActor *Actor, FAIStimulus Stimulus)
//{
//    if (GetTeamAttitudeTowards(*Actor) == ETeamAttitude::Hostile)
//    {
//        IsPatrolling = false;
//        StartChasingPlayer();
//    }
//    switch (Stimulus.Type)
//    {
//    case 0:
//    // react to sight stimulus
//    // GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("react to sight stimulus"));
//    case 1:
//        // react to hearing;
//        // GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("react to hearing"));
//    default:
//        return;
//    }
//}

// not done
//void AWolfAIController::ReturnToPatrol()
//{
//    if (controlledWolf->PatrolPath->IsValidLowLevel())
//    {
//        FVector closestLocation = controlledWolf->PatrolPath->FindLocationClosestToWorldLocation(controlledWolf->GetActorLocation(), ESplineCoordinateSpace::Type::World);
//
//        float distanceToPoint;
//        controlledWolf->CurrentPatrolPoint = controlledWolf->PatrolPath->GetSplinePointsPosition().InaccurateFindNearest(closestLocation, distanceToPoint);
//        MoveToLocation(closestLocation);
//        IsPatrolling = true;
//    }
//}
