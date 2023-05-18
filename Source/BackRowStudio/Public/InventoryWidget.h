#pragma once

#include "Blueprint/UserWidget.h"
#include "Components/GridPanel.h"
#include "CoreMinimal.h"
#include "InventoryWidget.generated.h"

UCLASS()
class BACKROWSTUDIO_API UInventoryWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    UFUNCTION(BlueprintCallable)
    void UpdateInventory();

    UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn))
    class UInventoryComponent *Inventory;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    UGridPanel *BagPanel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
    UGridPanel *SpellPanel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<class USlotWidget> SlotWidget;

    UPROPERTY(BlueprintReadWrite)
    USlotWidget *HoveredSlot;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int HorizontalLimit = 5;
};
