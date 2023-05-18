#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Wolf.h"
#include "WolfSpawningZone.generated.h"

UCLASS()
class BACKROWSTUDIO_API AWolfSpawningZone : public AActor
{
    GENERATED_BODY()

public:
    AWolfSpawningZone();

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool ShouldTrigger = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int SpawnAmount;

    UPROPERTY(EditAnywhere)
    class UBoxComponent *TriggeringZone;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    USphereComponent *SpawningZone;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<AWolf> WolfToSpawn;

    virtual void Tick(float delta_time) override;

    UFUNCTION(BlueprintCallable)
    void SpawnInTheWolves();

    UFUNCTION()
    void OnPickupOverlapBegin(UPrimitiveComponent *overlapped_component, AActor *other_actor, UPrimitiveComponent *other_comp, int32 other_body_index, bool b_from_sweep, const FHitResult &sweep_result);

};
