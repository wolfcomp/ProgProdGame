#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "MainCharacter.h"
#include "WolfAIController.h"
#include "WolfSpawningZone.h"

AWolfSpawningZone::AWolfSpawningZone()
{
    PrimaryActorTick.bCanEverTick = true;
    this->bGenerateOverlapEventsDuringLevelStreaming = true;
    TriggeringZone = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Hitbox"));
    SpawningZone = CreateDefaultSubobject<USphereComponent>(TEXT("Spawning Zone"));

    TriggeringZone->SetupAttachment(GetRootComponent());
    SpawningZone->SetupAttachment(TriggeringZone);

    TriggeringZone->SetGenerateOverlapEvents(true);
    TriggeringZone->OnComponentBeginOverlap.AddDynamic(this, &AWolfSpawningZone::OnPickupOverlapBegin);
}

void AWolfSpawningZone::BeginPlay() { Super::BeginPlay(); }

void AWolfSpawningZone::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

void AWolfSpawningZone::SpawnInTheWolves()
{
    for (int j = 0; j < SpawnAmount; ++j)
    {
        const FVector a1 = SpawningZone->GetComponentLocation();
        const FRotator lookAt = (GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - SpawningZone->GetComponentLocation()).Rotation();
        AActor *a = GetWorld()->SpawnActor(WolfToSpawn, &a1, &lookAt);
        AWolf *wolf = Cast<AWolf>(a);
        wolf->SpawnDefaultController();
        AWolfAIController *wolfController = Cast<AWolfAIController>(wolf->Controller);
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
