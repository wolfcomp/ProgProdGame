#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MainMenuLevel.generated.h"

UCLASS()
class BACKROWSTUDIO_API AMainMenuLevel : public ALevelScriptActor
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Main Menu")
    TSubclassOf<UUserWidget> MainMenuWidget;

    virtual void BeginPlay() override;
};
