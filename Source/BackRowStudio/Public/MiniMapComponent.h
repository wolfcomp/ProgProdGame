#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "MiniMapComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BACKROWSTUDIO_API UMiniMapComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UMiniMapComponent();

protected:
    virtual void BeginPlay() override;

public:
    virtual void TickComponent(float delta_time, ELevelTick tick_type, FActorComponentTickFunction *tick_function) override;
};
