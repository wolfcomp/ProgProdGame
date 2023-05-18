#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "MainCharacterPlayerController.generated.h"

UCLASS()
class BACKROWSTUDIO_API AMainCharacterPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
    GENERATED_BODY()

public:
    FGenericTeamId TeamId = FGenericTeamId(4);

    virtual FGenericTeamId GetGenericTeamId() const override;
};
