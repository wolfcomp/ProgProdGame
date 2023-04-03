// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "InventoryComponent.h"
#include "InvDragDropOperation.generated.h"

/**
 * 
 */
UCLASS()
class BACKROWSTUDIO_API UInvDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* WidgetReference;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D DragOffset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSlotStruct MyContent;
};
