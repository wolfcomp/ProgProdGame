#include "DebugSpellActor.h"

ADebugSpellActor::ADebugSpellActor()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ADebugSpellActor::BeginPlay()
{
    Super::BeginPlay();
    ISpellActor::Spell = Spell;
    DebugSpell(GetActorLocation(), GetActorRotation(), GetWorld());
    if (Spell != nullptr)
    {
        CastSpell(GetActorLocation(), GetActorRotation(), GetWorld(), RootComponent, Spell->DebugHeavy);
    }
}

void ADebugSpellActor::Tick(const float delta_time) { Super::Tick(delta_time); }

void ADebugSpellActor::LightAttack(FVector origin, FRotator rotation, UWorld *world, AActor *self, TArray<ADamageActor *> &actors, const bool apply_damage) { ISpellActor::LightAttack(origin, rotation, world, self, actors, false); }

void ADebugSpellActor::HeavyAttack(FVector origin, FRotator rotation, UWorld *world, AActor *self, TArray<ADamageActor *> &actors, const bool apply_damage) { ISpellActor::HeavyAttack(origin, rotation, world, self, actors, false); }
