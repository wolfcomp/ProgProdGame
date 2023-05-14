// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItemAsset.h"
#include "GameFramework/Actor.h"
#include "CheckpointActor.generated.h"

USTRUCT()
struct FCheckpointSave
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere)
    TArray<FSlotStruct> Items;

    UPROPERTY(VisibleAnywhere)
    TArray<FSlotStruct> Spells;

    UPROPERTY(VisibleAnywhere)
    int Health;

    UPROPERTY(VisibleAnywhere)
    TMap<uint32, FVector> EnemyLocations;

    UPROPERTY(VisibleAnywhere)
    TMap<uint32, bool> ItemsInWorld;

    UPROPERTY(VisibleAnywhere)
    FVector PlayerLocationOffset;
};

UCLASS()
class BACKROWSTUDIO_API ACheckpointActor : public AActor
{
    GENERATED_BODY()

public:
    ACheckpointActor();

    UPROPERTY(EditAnywhere, Category = "Checkpoint | Components")
    class UBoxComponent *CheckpointCollisionBox;

    UPROPERTY(EditAnywhere, Category = "Checkpoint | Components")
    UStaticMeshComponent *SpawnPoint;

    UPROPERTY(VisibleAnywhere, Category = "Checkpoint | Components")
    class UArrowComponent *SpawnPointArrow;

    UPROPERTY(VisibleAnywhere, Category = "Checkpoint | Saved Data")
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
