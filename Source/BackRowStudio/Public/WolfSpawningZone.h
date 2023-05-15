// Fill out your copyright notice in the Description page of Project Settings.

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
    // Sets default values for this actor's properties
    AWolfSpawningZone();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool ShouldTrigger = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int SpawnAmountPerSphere = 1;

    UPROPERTY(EditAnywhere)
    class UBoxComponent *TriggeringZone;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    USphereComponent *SpawningZone;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<AWolf> WolfToSpawn;

    // Called every frame
    virtual void Tick(float delta_time) override;

    UFUNCTION(BlueprintCallable)
    void SpawnInTheWolves();

    UFUNCTION()
    void OnPickupOverlapBegin(UPrimitiveComponent *overlapped_component, AActor *other_actor, UPrimitiveComponent *other_comp, int32 other_body_index, bool b_from_sweep, const FHitResult &sweep_result);

};
