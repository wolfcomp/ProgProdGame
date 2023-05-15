// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "OptionsMenu.generated.h"

/**
 * 
 */
UCLASS()
class BACKROWSTUDIO_API UOptionsMenu : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
    UButton *FullScreenButton;

    UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
    UButton *ExitButton;

    UFUNCTION()
    void ToggleFullScreen();
};
