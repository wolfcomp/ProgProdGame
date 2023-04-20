// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "Input/Reply.h"
#include "InventoryItemAsset.h"
#include "SlotWidget.generated.h"


UCLASS()
class BACKROWSTUDIO_API USlotWidget : public UUserWidget
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable)
    FSlotStruct AddContent(USlotWidget *InWidget);

    UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn))
    FSlotStruct MyContent;
};

// virtual void NativeConstruct() override;
// virtual bool NativeOnDrop(const FGeometry &InGeometry, const FDragDropEvent &InDragDropEvent, UDragDropOperation *InOperation) override;
// virtual void NativeOnDragDetected(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent, UDragDropOperation *&OutOperation) override;
// virtual void NativeOnDragCancelled(const FDragDropEvent &InDragDropEvent, UDragDropOperation *InOperation) override;
// virtual FReply NativeOnMouseButtonDown(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent) override;

// UFUNCTION()
//       FText SetQuantityField() const;
// UFUNCTION()
//       FSlateBrush SetImageField() const;
// UFUNCTION()
//    void Synchronize();

// UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
//       class UImage* MyImage;
// UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
//    class UTextBlock* QuantityNum;
// UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
//    class UBorder* QuantityTextBox;
// UPROPERTY()
//   FSlateBrush OrgImg;