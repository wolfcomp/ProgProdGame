#include "Enemy.h"

void ADamageActor::BeginPlay() { Super::BeginPlay(); }

void ADamageActor::Tick(float x) { Super::Tick(x); }

void ADamageActor::TakeDamage(int damage, AActor *actor)
{
    // Implement in sub actors
}

AEnemy::AEnemy()
{
    PrimaryActorTick.bCanEverTick = true;

    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
    StaticMesh->SetupAttachment(GetRootComponent());
}

void AEnemy::BeginPlay() { Super::BeginPlay(); }

void AEnemy::Tick(float delta_time) { Super::Tick(delta_time); }

void AEnemy::TakeDamage(int damage, AActor *actor)
{
    Health -= damage;
    if (Health <= 0)
    {
        Destroy();
    }
}
