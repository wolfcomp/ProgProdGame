// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpellActor.h"
#include "DebugSpellActor.generated.h"

UCLASS()
class BACKROWSTUDIO_API ADebugSpellActor : public AActor, public ISpellActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ADebugSpellActor();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float) override;

    virtual void LightAttack(FVector, FRotator, UWorld *, AActor *self, TArray<ADamageActor *> &, const bool apply_damage) override;

    virtual void HeavyAttack(FVector, FRotator, UWorld *, AActor *self, TArray<ADamageActor *> &, const bool apply_damage) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FSpell Spell;
};
