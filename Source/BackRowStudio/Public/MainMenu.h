// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OptionsMenu.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class BACKROWSTUDIO_API UMainMenu : public UUserWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
    UWidgetSwitcher *MyWidgetSwitcher;

    UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
    UButton *StartButton;

    UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
    UButton *OptionsButton;

    UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
    UOptionsMenu *OptionsMenu;


    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName LevelToLoad;

    virtual void NativeConstruct() override;

    UFUNCTION()
    void MyStartGame();

    UFUNCTION()
    void SwitchMenu();
};
