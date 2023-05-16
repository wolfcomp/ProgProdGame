// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PatrolPathActor.generated.h"

UCLASS()
class BACKROWSTUDIO_API APatrolPathActor : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    APatrolPathActor();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    UPROPERTY(EditAnywhere)
    class USplineComponent *PatrolPath;

    // Called every frame
    virtual void Tick(float DeltaTime) override;

};
