// Copyright Epic Games, Inc. All Rights Reserved.

#include "BackRowStudioGameMode.h"
#include "BackRowStudioCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABackRowStudioGameMode::ABackRowStudioGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
