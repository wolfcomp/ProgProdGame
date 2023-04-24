// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/PlayerController.h"
#include "MainCharacterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BACKROWSTUDIO_API AMainCharacterPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

	public:
	FGenericTeamId TeamId = FGenericTeamId(4);
	virtual FGenericTeamId GetGenericTeamId() const override;
};
