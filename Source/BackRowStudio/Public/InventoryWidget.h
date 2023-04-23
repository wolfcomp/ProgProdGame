// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "Components/GridPanel.h"
#include "CoreMinimal.h"
#include "InventoryComponent.h"
#include "SlotWidget.h"
#include "InventoryWidget.generated.h"

UCLASS()
class BACKROWSTUDIO_API UInventoryWidget : public UUserWidget
{
    GENERATED_BODY()
public:
    virtual void NativeTick(const FGeometry &geometry, float delta_time) override;

    virtual void NativePreConstruct() override;

    virtual void NativeConstruct() override;

    UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn))
    class UInventoryComponent *Inventory;

    UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    UGridPanel *MyGridPanel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<USlotWidget> MySlotWidget;

    UPROPERTY(BlueprintReadWrite)
    TSubclassOf<USlotWidget> SlotWidget;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int HorizontalLimit = 5;
};
