// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugSpellActor.h"

// Sets default values
ADebugSpellActor::ADebugSpellActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADebugSpellActor::BeginPlay()
{
    Super::BeginPlay();
    ISpellActor::Spell = Spell;
    DebugSpell(GetActorLocation(), GetActorRotation(), GetWorld());
}

// Called every frame
void ADebugSpellActor::Tick(const float delta_time) { Super::Tick(delta_time); }

void ADebugSpellActor::LightAttack(const FVector origin, const FRotator rotation, UWorld *world, TArray<AActor*> actors) { ISpellActor::LightAttack(origin, rotation, world, actors); }

void ADebugSpellActor::HeavyAttack(const FVector origin, const FRotator rotation, UWorld *world, TArray<AActor*> actors) { ISpellActor::HeavyAttack(origin, rotation, world, actors); }
