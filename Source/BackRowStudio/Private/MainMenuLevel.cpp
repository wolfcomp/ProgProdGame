// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuLevel.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void AMainMenuLevel::BeginPlay()
{
    if (MainMenuWidget->IsValidLowLevel())
    {
        UUserWidget* myWidget = CreateWidget(GetWorld(), MainMenuWidget);
        myWidget->AddToViewport();
    }
    Super::BeginPlay();
}
