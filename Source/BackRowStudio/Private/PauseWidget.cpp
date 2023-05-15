// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseWidget.h"

#include "OptionsMenu.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"


void UPauseWidget::DoOnCreate()
{
    UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(PC, this);
    PC->SetShowMouseCursor(true);
    PC->SetPause(true);
    this->SetVisibility(ESlateVisibility::Visible);
}

void UPauseWidget::DoOnDestroy()
{
    UWidgetBlueprintLibrary::SetInputMode_GameOnly(PC);
    PC->SetShowMouseCursor(false);
    PC->SetPause(false);
    this->SetVisibility(ESlateVisibility::Collapsed);
}

void UPauseWidget::NativeConstruct()
{
    Super::NativeConstruct();
    OptionsButton->OnClicked.AddDynamic(this, &UPauseWidget::SwitchMenu);
    OptionsMenu->ExitButton->OnClicked.AddDynamic(this, &UPauseWidget::SwitchMenu);
    ExitButton->OnClicked.AddDynamic(this, &UPauseWidget::ExitGame);
}

void UPauseWidget::SwitchMenu()
{
    if (MyWidgetSwitcher->GetActiveWidgetIndex() == 1)
    {
        MyWidgetSwitcher->SetActiveWidgetIndex(0);
    }
    else
    {
        MyWidgetSwitcher->SetActiveWidgetIndex(1);
    }
}

void UPauseWidget::ExitGame()
{
    UGameplayStatics::OpenLevel(this, MainMenuLevel);
}
