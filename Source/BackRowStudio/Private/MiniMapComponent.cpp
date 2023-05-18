#include "MiniMapComponent.h"

UMiniMapComponent::UMiniMapComponent() { PrimaryComponentTick.bCanEverTick = true; }

void UMiniMapComponent::BeginPlay() { Super::BeginPlay(); }

void UMiniMapComponent::TickComponent(float delta_time, ELevelTick tick_type, FActorComponentTickFunction *tick_function)
{
}
