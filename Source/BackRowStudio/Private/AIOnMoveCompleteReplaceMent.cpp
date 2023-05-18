// Fill out your copyright notice in the Description page of Project Settings.


#include "AIOnMoveCompleteReplaceMent.h"
#include "Wolf.h"
#include "WolfAIController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAIOnMoveCompleteReplaceMent::AAIOnMoveCompleteReplaceMent()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAIOnMoveCompleteReplaceMent::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void AAIOnMoveCompleteReplaceMent::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    TArray<AActor *> actors;
    UGameplayStatics::GetAllActorsOfClass(this, AWolf::StaticClass(), actors);

    for (int i = 0; i < actors.Num(); ++i)
    {
        if (const AWolf *wolf = Cast<AWolf>(actors[i]); wolf->IsValidLowLevel())
        {
            if (wolf->Patrol == true)
            {
                if (float dist = FVector::Dist(wolf->GetActorLocation(), wolf->WolfAIController->PatrolPoints[wolf->WolfAIController->CurrentPatrolPointIndex]); dist < 300)
                {
                    wolf->WolfAIController->Patrol();
                }
            }
        }
    }
}
