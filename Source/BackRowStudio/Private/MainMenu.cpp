// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMainMenu::MyStartGame()
{
	if (GameLevel.IsValid())
	{
		UGameplayStatics::OpenLevel(this, FName(GameLevel->GetMapName()));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green,TEXT("main menu widget has invalid level"));
	}
}
