#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PatrolPathActor.generated.h"

UCLASS()
class BACKROWSTUDIO_API APatrolPathActor : public AActor
{
    GENERATED_BODY()

public:
    APatrolPathActor();

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(EditAnywhere)
    class USplineComponent *PatrolPath;

    virtual void Tick(float DeltaTime) override;

};
