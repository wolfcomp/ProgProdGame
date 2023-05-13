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

	navArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
	bMoveToPlayer = false;

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
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ThisClass::OnTargetPerceptionUpdatedDelegate);
}

void AWolfAIController::MoveToPlayer()
{
	if (PlayerMoveTimeTilNextCheck <= GetWorld()->TimeSeconds)
	{
		const FAIMoveRequest nextPatrolPoint = FAIMoveRequest(controlledWolf->PlayerRef->GetNavAgentLocation());
		if (const double distance = FVector::Dist(controlledWolf->GetNavAgentLocation(),
		                                          controlledWolf->PlayerRef->GetNavAgentLocation()); nextPatrolPoint.
			IsValid() && distance > 100)
		{
			MoveToActor(controlledWolf->PlayerRef);
			bMoveToPlayer = true;
		}
		else if (distance <= controlledWolf->PlayerAttackCollisionDetectionRadius)
		{
			controlledWolf->TryAttack(controlledWolf->PlayerRef);
			bMoveToPlayer = false;
			FTimerHandle poggersProtector;
			GetWorld()->GetTimerManager().SetTimer(
				poggersProtector,
				[&]()
				{
					bMoveToPlayer = true;
					controlledWolf->TryStoppingAttack();
					if (!IsFollowingAPath())
					{
						MoveToPlayer();
					}
				},
				1, false);
		}
		else
		{
			controlledWolf->TryStoppingAttack();
		}
		PlayerMoveTimeTilNextCheck = GetWorld()->TimeSeconds + 1;
	}
}

void AWolfAIController::Patrol()
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
}

void AWolfAIController::OnMoveCompleted(FAIRequestID request_id, const FPathFollowingResult& result)
{
	if (result.IsSuccess() && !result.IsInterrupted())
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
	// Super::OnMoveCompleted(requestID, result);
}

ETeamAttitude::Type AWolfAIController::GetTeamAttitudeTowards(const AActor& other) const
{
	if (APawn const* otherPawn = Cast<APawn>(&other))
	{
		if (auto const teamAgent = Cast<IGenericTeamAgentInterface>(otherPawn->GetController()))
		{
			if (teamAgent->GetGenericTeamId() == FGenericTeamId(0) || teamAgent->GetGenericTeamId() ==
				FGenericTeamId(1))
			{
				return ETeamAttitude::Friendly;
			}
			return ETeamAttitude::Hostile;
		}
	}
	return ETeamAttitude::Neutral;
}

void AWolfAIController::OnTargetPerceptionUpdatedDelegate(AActor* actor, FAIStimulus stimulus)
{
	if (GetTeamAttitudeTowards(*actor) == ETeamAttitude::Hostile)
	{
		MoveToPlayer();
	}
	switch (stimulus.Type)
	{
	case 0:
	// react to sight stimulus

	case 1:
		// react to hearing;
	default:
		return;
	}
}
