// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

void UMainMenu::NativeConstruct()
{
    Super::NativeConstruct();
    StartButton->OnClicked.AddDynamic(this, &UMainMenu::MyStartGame);
    OptionsButton->OnClicked.AddDynamic(this, &UMainMenu::SwitchMenu);
    OptionsMenu->ExitButton->OnClicked.AddDynamic(this, &UMainMenu::SwitchMenu);
}

void UMainMenu::MyStartGame()
{
    GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
    UGameplayStatics::OpenLevel(this, LevelToLoad);
}

void UMainMenu::SwitchMenu()
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
