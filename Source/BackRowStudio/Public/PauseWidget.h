// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "PauseWidget.generated.h"

/**
 *
 */
UCLASS()
class BACKROWSTUDIO_API UPauseWidget : public UUserWidget
{
    GENERATED_BODY()
public:
    void DoOnCreate();

    void DoOnDestroy();

    // Player Controller reference
    UPROPERTY()
    APlayerController *PC;
};
