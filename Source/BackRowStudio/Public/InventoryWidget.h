// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryComponent.h"
#include "SlotWidget.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/UserWidgetBlueprint.h"
#include "Components/HorizontalBox.h"
#include "Components/VerticalBox.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class BACKROWSTUDIO_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeTick(const FGeometry &MyGeometry, float InDeltaTime) override;
	virtual void NativePreConstruct() override;
	UPROPERTY(BlueprintReadWrite, meta=(ExposeOnSpawn))
    TArray<FSlotStruct> MyInventory;
	TArray<FSlotStruct> MyInv;

	//UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	//UVerticalBox* MyVertical;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UHorizontalBox* MyHorizontal;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USlotWidget> MySlotWidget;
	UPROPERTY()
	//TSubclassOf<USlotWidget>* MySlotW;
	USlotWidget* temp;
};
