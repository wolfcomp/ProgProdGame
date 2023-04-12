// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItemAsset.h"
#include "DragPreview.generated.h"

/**
 * 
 */
UCLASS()
class BACKROWSTUDIO_API UDragPreview : public UUserWidget
{
	GENERATED_BODY()
public:
	FSlotStruct Content;

	UPROPERTY()
	UTexture2D* Image;
	UPROPERTY(meta = (BindWidget))
    class UImage* MyImage;

	FVector2D MousePos = FVector2D(0,0);


    UFUNCTION()
    FSlateBrush SetImageField() const;
	virtual void NativeTick(const FGeometry &MyGeometry, float InDeltaTime) override;
	virtual void NativeConstruct() override;
};
