// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "MinimapWidget.generated.h"

/**
 * 
 */
UCLASS()
class BACKROWSTUDIO_API UMinimapWidget : public UUserWidget
{
	GENERATED_BODY()
	//virtual void NativeConstruct() override;
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta=(ExposeOnSpawn))
		 class UMaterial* MyMat;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn))
    class UMiniMapComponent* MyParent;
};
