#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "InventoryItemAsset.h"
#include "InventoryComponent.generated.h"


class UInventoryWidget;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BACKROWSTUDIO_API UInventoryComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UInventoryComponent();

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
    TArray<FSlotStruct> Items;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
    TArray<FSlotStruct> Spells;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int NumberOfInventorySlots = 15;

    UFUNCTION(BlueprintCallable)
    bool AddItem(FSlotStruct item);

    UFUNCTION(BlueprintCallable)
    bool AddSpell(FSlotStruct spell);

protected:
    virtual void BeginPlay() override;

public:
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
};
