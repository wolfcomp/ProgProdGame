#include "PatrolPathActor.h"
#include "Components/SplineComponent.h"

APatrolPathActor::APatrolPathActor()
{
    PrimaryActorTick.bCanEverTick = true;
    PatrolPath = CreateDefaultSubobject<USplineComponent>(TEXT("Wolf Patrol Path"));
    PatrolPath->SetupAttachment(RootComponent);
}

void APatrolPathActor::BeginPlay() { Super::BeginPlay(); }

void APatrolPathActor::Tick(float DeltaTime) { Super::Tick(DeltaTime); }
