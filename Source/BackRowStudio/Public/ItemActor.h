#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemActor.generated.h"

UCLASS()
class BACKROWSTUDIO_API AItemActor : public AActor
{
    GENERATED_BODY()

public:
    AItemActor();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    class UInventoryItemAsset *Item;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
    UStaticMeshComponent *Mesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collider")
    class USphereComponent *SphereCollider;

    bool IsPickedUp;

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float delta_time) override;
};
