// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniMapComponent.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "GameFramework/GameSession.h"
#include "MinimapWidget.h"

UMiniMapComponent::UMiniMapComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UMiniMapComponent::BeginPlay() { Super::BeginPlay(); }

void UMiniMapComponent::TickComponent(float delta_time, ELevelTick tick_type, FActorComponentTickFunction *tick_function) {}
