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
    if(Spell != nullptr)
        CastSpell(GetActorLocation(), GetActorRotation(), GetWorld(), RootComponent, Spell->DebugHeavy);
}

// Called every frame
void ADebugSpellActor::Tick(const float delta_time) { Super::Tick(delta_time); }

void ADebugSpellActor::LightAttack(FVector origin, FRotator rotation, UWorld *world, AActor *self, TArray<ADamageActor *> &actors, const bool apply_damage) { ISpellActor::LightAttack(origin, rotation, world, self, actors, false); }

void ADebugSpellActor::HeavyAttack(FVector origin, FRotator rotation, UWorld *world, AActor *self, TArray<ADamageActor *> &actors, const bool apply_damage) { ISpellActor::HeavyAttack(origin, rotation, world, self, actors, false); }
