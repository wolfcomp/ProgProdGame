// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckpointActor.generated.h"

USTRUCT()
struct FCheckpointSave
{
    GENERATED_BODY()

    TArray<struct FSlotStruct> Items;

    TArray<FSlotStruct> Spells;

    int Health;

    TMap<uint32, FVector> EnemyLocations;

    TMap<uint32, bool> ItemsInWorld;
};

UCLASS()
class BACKROWSTUDIO_API ACheckpointActor : public AActor
{
    GENERATED_BODY()

public:
    ACheckpointActor();

    UPROPERTY(EditAnywhere, Category = "Checkpoint")
    class UBoxComponent *CheckpointCollisionBox;

    UPROPERTY(EditAnywhere, Category = "Checkpoint")
    UStaticMeshComponent *SpawnPoint;

    UPROPERTY(VisibleAnywhere, Category = "Checkpoint")
    UArrowComponent *SpawnPointArrow;

    UPROPERTY(VisibleAnywhere, Category = "Checkpoint")
    bool IsTriggered;

    UPROPERTY(VisibleAnywhere, Category = "Checkpoint | Saved Data")
    FCheckpointSave SavedData;

protected:
    virtual void BeginPlay() override;

public:
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent *overlapped_component, AActor *other_actor, UPrimitiveComponent *other_component, int other_index, bool from_sweep, const FHitResult &sweep_result);
    void RespawnOthers();

    void RespawnPlayer(class AMainCharacter *player);
};
