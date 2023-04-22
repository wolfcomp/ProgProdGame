// Fill out your copyright notice in the Description page of Project Settings.


#include "WolfAIController.h"

#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"

#include "Wolf.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "MainCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void AWolfAIController::BeginPlay()
{
    Super::BeginPlay();

    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);

    bSearchForPlayer = true;
    bCanAttackPlayer = true;
    bMoveToPlayer = false;

    GenerateRandomSearchLocation();
    SearchForPlayer();

    //GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("BeginPlay"));

}

void AWolfAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void AWolfAIController::GenerateRandomSearchLocation()
{
    //GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("GenerateRandomSearchLocation"));
    FNavLocation result;
    if(NavArea->GetRandomReachablePointInRadius(GetPawn()->GetActorLocation(), 10000.0f, result))
    {
        RandomLocation = result.Location;
    };
}

void AWolfAIController::SearchForPlayer()
{
    //GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("SearchForPlayer"));
    MoveToLocation(RandomLocation);
}

void AWolfAIController::MoveToPlayer()
{
}

void AWolfAIController::StartChasingPlayer()
{
}

bool AWolfAIController::IsWolfCloseToPlayer()
{
    return false;
}

void AWolfAIController::AttackPlayer()
{
}

void AWolfAIController::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
    Super::OnMoveCompleted(RequestID, Result);

    if (bSearchForPlayer)
    {
        GenerateRandomSearchLocation();
        SearchForPlayer();
    }
}

void AWolfAIController::OnDetectPlayerBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
}

void AWolfAIController::OnDetectPlayerEndOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
}
