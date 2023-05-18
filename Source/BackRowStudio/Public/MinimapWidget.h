#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "MinimapWidget.generated.h"

UCLASS()
class BACKROWSTUDIO_API UMinimapWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn))
    class UMaterial *MyMat;
};
