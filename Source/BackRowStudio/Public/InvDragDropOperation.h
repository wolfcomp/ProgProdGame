// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "InvDragDropOperation.generated.h"

/**
 * 
 */
UCLASS()
class BACKROWSTUDIO_API UInvDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FVector2D DragOffset;
	UPROPERTY()
	UUserWidget* WidgetReference;
};
