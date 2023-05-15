// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "OptionsMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
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

    virtual void NativeConstruct() override;

    UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
    UWidgetSwitcher *MyWidgetSwitcher;

    UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
    UButton *ExitButton;

    UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
    UButton *OptionsButton;

    UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
    UOptionsMenu *OptionsMenu;

    // Player Controller reference
    UPROPERTY()
    APlayerController *PC;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName MainMenuLevel;

    UFUNCTION()
    void SwitchMenu();
    UFUNCTION()
    void ExitGame();
};
