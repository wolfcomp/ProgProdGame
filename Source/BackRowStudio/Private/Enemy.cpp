// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

void ADamageActor::BeginPlay() { Super::BeginPlay(); }

void ADamageActor::Tick(float x) { Super::Tick(x); }

void ADamageActor::TakeDamage(int damage, AActor *actor)
{
    // Implement in sub actors
}

// Sets default values
AEnemy::AEnemy()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
    StaticMesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay() { Super::BeginPlay(); }

// Called every frame
void AEnemy::Tick(float delta_time) { Super::Tick(delta_time); }

void AEnemy::TakeDamage(int damage, AActor *actor)
{
    Health -= damage;
    if (Health <= 0)
    {
        Destroy();
    }
}
