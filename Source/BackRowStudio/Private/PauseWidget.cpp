// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"


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
