#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

UCLASS()
class BACKROWSTUDIO_API UHealthBarWidget : public UUserWidget
{
    GENERATED_BODY()
    virtual void NativeConstruct() override;

public:
    UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
    class UProgressBar *MyHealthBar;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class AMainCharacter *MyPlayer;

    UFUNCTION()
    float GetHealth() const;
};
