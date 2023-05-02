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
			if (controlledWolf->PatrolPath->GetWorldLocationAtSplinePoint(i) != FVector(0, 0, 0))
			{
				patrolPoints.Add(controlledWolf->PatrolPath->GetWorldLocationAtSplinePoint(i));
				//DrawDebugSphere(GetWorld(), controlledWolf->PatrolPath->GetWorldLocationAtSplinePoint(i), 200, 16, FColor::Green);
			}
		}
		//MoveToLocation(patrolPoints[controlledWolf->CurrentPatrolPoint]);
		//controlledWolf->CurrentPatrolPoint++;
		Patrol();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Dafuq am i Controlling? -WolfAiController"));
	}

	//if (IsInitialized)
	//{
	//	if (controlledWolf->PatrolPath->IsValidLowLevel() && controlledWolf->PatrolPath->GetNumberOfSplinePoints() > 0
	//		&& IsPatrolling == true)
	//	{
	//		bSearchForPlayer = false;
	//		Patrol();
	//		//SearchForPlayer();
	//	}
	//	else
	//	{
	//		SearchForPlayer();
	//	}
	//}
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
	//if (FNavLocation result; NavArea->GetRandomReachablePointInRadius(GetPawn()->GetActorLocation(), 10000.0f, result))
	//{
	//	RandomLocation = result.Location;
	//};
}

void AWolfAIController::SearchForPlayer()
{
	//if (!IsPointReachable(RandomLocation) || RandomLocation == FVector())
	//{
	//	GenerateRandomSearchLocation();
	//}
	//MoveToLocation(RandomLocation);
}

void AWolfAIController::OnActiveFinishedMove()
{
	//if (IsPatrolling)
	//{
	//	Patrol();
	//}
	//else if (bMoveToPlayer)
	//{
	//	MoveToPlayer();
	//}
	//else if (bSearchForPlayer)
	//{
	//	GenerateRandomSearchLocation();
	//	SearchForPlayer();
	//}
	//else
	//{
	//	bIsActive = false;
	//}
}

void AWolfAIController::MoveToPlayer()
{
	if (playerMoveTimeTilNextCheck <= GetWorld()->TimeSeconds)
	{
		if (IsPointReachable(controlledWolf->PlayerRef->GetActorLocation()))
		{
			MoveToLocation(controlledWolf->PlayerRef->GetActorLocation());
			bSearchForPlayer = false;
			bMoveToPlayer = true;
			IsPatrolling = false;
		}
		else if (controlledWolf->IsValidLowLevel())
		{
			controlledWolf->PlayerDetected = false;
			controlledWolf->CurrentSpotRadius = 640;
			bMoveToPlayer = false;
			//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red,TEXT("didn't work 1"));
		}
		playerMoveTimeTilNextCheck = GetWorld()->TimeSeconds + 1;
	}
}

bool AWolfAIController::IsPointReachable(FVector point) const
{
	FPathFindingQuery A14;
	FNavLocation a15;
	NavArea->GetRandomReachablePointInRadius(point, 10, a15);
	const FPathFindingResult pathResult = NavArea->GetAbstractNavData()->
	                                               FindPath(this->GetNavAgentPropertiesRef(), A14);
	if (pathResult.Result != ENavigationQueryResult::Error && pathResult.IsSuccessful() && pathResult.Path.IsValid() &&
		!pathResult.IsPartial())
	{
		return true;
	}
	if (!a15.HasNodeRef())
	{
		//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, a15.Location.ToString());
		return true;
	}
	else if (pathResult.Result == ENavigationQueryResult::Error)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red,TEXT("1 wolf.cpp 172"));
		//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red,);
	}
	else if (!pathResult.IsSuccessful())
	{
		//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red,TEXT("2 wolf.cpp 176"));
	}
	else if (!pathResult.Path.IsValid())
	{
		//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red,TEXT("3 wolf.cpp 180"));
	}
	return false;
}

void AWolfAIController::Patrol()
{
	if (PatrolMoveTimeTilNextCheck <= GetWorld()->TimeSeconds)
	{
		if (IsPointReachable(patrolPoints[controlledWolf->CurrentPatrolPoint]))
		{
			//DrawDebugSphere(GetWorld(), CurrentPatrolPoint, 100, 16, FColor::Green, true, 100);
			//GEngine->AddOnScreenDebugMessage(4, 3.f, FColor::Yellow, TEXT("moving"));
			//auto nextPatrolPoint = FAIMoveRequest(patrolPoints[controlledWolf->CurrentPatrolPoint]);
			//MoveTo(nextPatrolPoint);
			MoveToLocation(CurrentPatrolPoint);
		}
		else
		{
			//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("didn't work 2"));
		}
		if (controlledWolf->CurrentPatrolPoint + 1 < patrolPoints.Num())
		{
			controlledWolf->CurrentPatrolPoint++;
		}
		else
		{
			controlledWolf->CurrentPatrolPoint = 0;
		}
		CurrentPatrolPoint = FNavLocation(patrolPoints[controlledWolf->CurrentPatrolPoint]);
		playerMoveTimeTilNextCheck = GetWorld()->TimeSeconds + 1;
	}

	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("2"));
	//DrawDebugSphere(GetWorld(), patrolPoints[controlledWolf->CurrentPatrolPoint], 200, 16, FColor::Red, true, 100000);
	//if (IsPatrolling && controlledWolf->PatrolPath->IsValidLowLevel() /*&& controlledWolf->PatrolPath->IsClosedLoop() &&
	//	controlledWolf->IsValidLowLevel() && patrolPoints.IsValidIndex(0) && bIsActive*/)
	//{
	//	if (/*IsPointReachable(patrolPoints[controlledWolf->CurrentPatrolPoint])*/ true)
	//	{
	//		MoveToLocation(patrolPoints[controlledWolf->CurrentPatrolPoint]);
	//		return;
	//	}
	//}
	//bIsActive = false;
}

void AWolfAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	//GEngine->AddOnScreenDebugMessage(5, 3.f, FColor::Red, Result.ToString());
	if (Result.IsSuccess() && !Result.IsInterrupted())
	{
		if (controlledWolf->PlayerDetected)
		{
			MoveToPlayer();
		}
		else
		{
			Patrol();
		}
		//FTimerHandle timerHandle;
		//GetWorld()->GetTimerManager().SetTimer(timerHandle, [&]()
		//{
		//	Patrol();
		//	UE_LOG(LogTemp, Warning, TEXT("This text will appear in the console 3 seconds after execution"))
		//}, 3, false);
		//if (bMoveToPlayer)
		//{
		//	MoveToPlayer();
		//}
		//else
		//{
		//	Patrol();
		//}
	}
	//Super::OnMoveCompleted(RequestID, Result);
}

void AWolfAIController::Reactivate()
{
	//if (!bIsActive)
	//{
	//	bIsActive = true;
	//}
	//OnActiveFinishedMove();
}

void AWolfAIController::Deactivate()
{
	//bIsActive = false;
	//if (IsFollowingAPath())
	//{
	//	StopMovement();
	//}
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
void AWolfAIController::ReturnToPatrol()
{
	//if (controlledWolf->PatrolPath->IsValidLowLevel())
	//{
	//	if (IsFollowingAPath())
	//	{
	//		StopMovement();
	//	}
	//	Patrol();
	//}
}
