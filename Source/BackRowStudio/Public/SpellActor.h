// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellActor.generated.h"
/**
 *
 */

class ADamageActor;

UENUM(BlueprintType)
enum class ESpellType : uint8
{
    Circle UMETA(DisplayName = "Circle"),
    Cone UMETA(DisplayName = "Cone"),
    Line UMETA(DisplayName = "Line"),
};

UINTERFACE(MinimalAPI, Blueprintable)
class USpellActor : public UInterface
{
    GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FSpellInternal
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector Range;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Radius;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Cooldown;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CastTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int Potency;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ESpellType Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UNiagaraSystem *VFX;
};

UCLASS(BlueprintType)
class USpell : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FSpellInternal Light;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FSpellInternal Heavy;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
    bool DebugLight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
    bool DebugHeavy;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<TObjectPtr<ADamageActor>> Hits;
};

class ISpellActor
{
    GENERATED_BODY()

    void InternalDebugSpell(ESpellType, FVector, float, FVector, FRotator, const UWorld *) const;

    TArray<ADamageActor *> GetActors(ESpellType, FVector, float, FVector, FRotator, UWorld *) const;

public:
    USpell* Spell;

    void CastSpell(FVector, FRotator, UWorld *, USceneComponent *, bool = false);

    void DebugSpell(FVector, FRotator, const UWorld *) const;

    virtual void LightAttack(FVector, FRotator, UWorld *, AActor *self, TArray<ADamageActor *> &actors, const bool apply_damage);

    virtual void HeavyAttack(FVector, FRotator, UWorld *, AActor *self, TArray<ADamageActor *> &actors, const bool apply_damage);
};
