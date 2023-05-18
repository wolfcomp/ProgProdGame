#include "MainMenuLevel.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void AMainMenuLevel::BeginPlay()
{
    if (MainMenuWidget->IsValidLowLevel())
    {
        APlayerController *controller = GetWorld()->GetFirstPlayerController();

        UUserWidget *myWidget = CreateWidget(GetWorld(), MainMenuWidget);

        myWidget->AddToViewport();
        controller->SetShowMouseCursor(true);
        UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(controller);
    }
    Super::BeginPlay();
}
