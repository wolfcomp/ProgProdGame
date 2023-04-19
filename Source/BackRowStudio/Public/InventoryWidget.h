// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SlotWidget.h"
#include "InventoryComponent.h"
#include "Components/GridPanel.h"
#include "InventoryWidget.generated.h"

UCLASS()
class BACKROWSTUDIO_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeTick(const FGeometry &MyGeometry, float InDeltaTime) override;
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, meta=(ExposeOnSpawn))
	    UInventoryComponent* MyInventory;
	UInventoryComponent* Inventory;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	    UGridPanel* MyGridPanel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	    TSubclassOf<USlotWidget> MySlotWidget;

	UPROPERTY(BlueprintReadWrite)
    TSubclassOf<USlotWidget> SlotWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	    int HorizontalLimit = 5;
};
