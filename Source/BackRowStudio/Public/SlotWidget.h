// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryComponent.h"
#include "Blueprint/UserWidget.h"
#include "Input/Reply.h"
#include "SlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class BACKROWSTUDIO_API USlotWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual bool NativeOnDrop(const FGeometry &InGeometry, const FDragDropEvent &InDragDropEvent, UDragDropOperation *InOperation) override;
	virtual void NativeOnDragDetected(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent, UDragDropOperation *&OutOperation) override;
	virtual void NativeOnDragCancelled(const FDragDropEvent &InDragDropEvent, UDragDropOperation *InOperation) override;


	FSlotStruct* OldContent;

	UFUNCTION()
    FText SetQuantityField() const;
	UFUNCTION()
    FSlateBrush SetImageField() const;
	
	virtual FReply NativeOnMouseButtonDown(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn))
	FSlotStruct MyContent;
	FSlotStruct* MyCon;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
    class UImage* MyImage = __nullptr;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* QuantityNum = __nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UBorder* QuantityTextBox = __nullptr;
};
