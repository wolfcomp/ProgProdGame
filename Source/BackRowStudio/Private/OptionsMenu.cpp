#include "OptionsMenu.h"
#include "GameFramework/GameUserSettings.h"
#include "Sound/SoundClass.h"

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
    }
    else
    {
        GEngine->GameUserSettings->SetFullscreenMode(EWindowMode::Windowed);
        GEngine->GameUserSettings->ApplySettings(false);
    }
}
