// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionsMenu.h"
#include "Sound/SoundClass.h"
#include "GameFramework/GameUserSettings.h"

void UOptionsMenu::NativeConstruct()
{
    FullScreenButton->OnClicked.AddDynamic(this, &UOptionsMenu::ToggleFullScreen);
    Super::NativeConstruct();
}

void UOptionsMenu::ToggleFullScreen()
{

    if (GEngine->GameUserSettings->GetFullscreenMode() != EWindowMode::Fullscreen)
    {
        GEngine->GameUserSettings->SetFullscreenMode(EWindowMode::Fullscreen);
        GEngine->GameUserSettings->ApplySettings(false);
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green,TEXT("False"));
    }
    else
    {
        GEngine->GameUserSettings->SetFullscreenMode(EWindowMode::Windowed);
        GEngine->GameUserSettings->ApplySettings(false);
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green,TEXT("True"));
    };
}
