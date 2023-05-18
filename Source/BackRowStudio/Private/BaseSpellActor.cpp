#include "BaseSpellActor.h"

ABaseSpellActor::ABaseSpellActor() { PrimaryActorTick.bCanEverTick = true; }

void ABaseSpellActor::BeginPlay()
{
    Super::BeginPlay();
    SetData();
}

void ABaseSpellActor::Tick(const float delta_time) { Super::Tick(delta_time); }

void ABaseSpellActor::SetData() { ISpellActor::Spell = Spell; }

void ABaseSpellActor::LightAttack(FVector origin, FRotator rotation, UWorld *world, AActor *self, TArray<ADamageActor *> &actors, const bool apply_damage) { ISpellActor::LightAttack(origin, rotation, world, self, actors, false); }

void ABaseSpellActor::HeavyAttack(FVector origin, FRotator rotation, UWorld *world, AActor *self, TArray<ADamageActor *> &actors, const bool apply_damage) { ISpellActor::HeavyAttack(origin, rotation, world, self, actors, false); }
