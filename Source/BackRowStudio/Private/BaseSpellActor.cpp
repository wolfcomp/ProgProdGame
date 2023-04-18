// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSpellActor.h"

// Sets default values
ABaseSpellActor::ABaseSpellActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseSpellActor::BeginPlay()
{
    Super::BeginPlay();
    ISpellActor::Spell = Spell;
}

// Called every frame
void ABaseSpellActor::Tick(const float delta_time) { Super::Tick(delta_time); }

void ABaseSpellActor::LightAttack(FVector origin, FRotator rotation, UWorld *world, AActor *self, TArray<ADamageActor *> &actors, const bool apply_damage) { ISpellActor::LightAttack(origin, rotation, world, self, actors, false); }

void ABaseSpellActor::HeavyAttack(FVector origin, FRotator rotation, UWorld *world, AActor *self, TArray<ADamageActor *> &actors, const bool apply_damage) { ISpellActor::HeavyAttack(origin, rotation, world, self, actors, false); }
