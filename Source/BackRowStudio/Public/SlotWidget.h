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