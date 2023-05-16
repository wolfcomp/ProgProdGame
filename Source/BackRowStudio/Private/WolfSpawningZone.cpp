// Fill out your copyright notice in the Description page of Project Settings.


#include "WolfSpawningZone.h"

#include "MainCharacter.h"
#include "WolfAIController.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AWolfSpawningZone::AWolfSpawningZone()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    this->bGenerateOverlapEventsDuringLevelStreaming = true;
    TriggeringZone = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Hitbox"));
    SpawningZone = CreateDefaultSubobject<USphereComponent>(TEXT("Spawning Zone"));

    TriggeringZone->SetupAttachment(RootComponent);
    SpawningZone->SetupAttachment(RootComponent);

    TriggeringZone->SetGenerateOverlapEvents(true);
    TriggeringZone->OnComponentBeginOverlap.AddDynamic(this, &AWolfSpawningZone::OnPickupOverlapBegin);
}

// Called when the game starts or when spawned
void AWolfSpawningZone::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void AWolfSpawningZone::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void AWolfSpawningZone::SpawnInTheWolves()
{
    for (int j = 0; j < SpawnAmount; ++j)
    {
        const FVector a1 = SpawningZone->GetComponentLocation();
        const FRotator lookAt = (GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - SpawningZone->GetComponentLocation()).Rotation();
        GetWorld()->SpawnActor(WolfToSpawn, &a1, &lookAt);
    }
}

void AWolfSpawningZone::OnPickupOverlapBegin(UPrimitiveComponent *overlapped_component, AActor *other_actor, UPrimitiveComponent *other_comp, int32 other_body_index, bool b_from_sweep, const FHitResult &sweep_result)
{
    if (const AMainCharacter *playerChar = Cast<AMainCharacter>(other_actor); playerChar->IsValidLowLevel())
    {
        if (ShouldTrigger && WolfToSpawn->IsValidLowLevel())
        {
            SpawnInTheWolves();
            ShouldTrigger = false;
        }
    }
}
