#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpellActor.h"
#include "BaseSpellActor.generated.h"

UCLASS()
class BACKROWSTUDIO_API ABaseSpellActor : public AActor, public ISpellActor
{
    GENERATED_BODY()

public:
    ABaseSpellActor();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    void SetData();

    virtual void LightAttack(FVector, FRotator, UWorld *, AActor *self, TArray<ADamageActor *> &, const bool apply_damage) override;

    virtual void HeavyAttack(FVector, FRotator, UWorld *, AActor *self, TArray<ADamageActor *> &, const bool apply_damage) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    USpell *Spell;
};
