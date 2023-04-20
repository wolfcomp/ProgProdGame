// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class ADamageActor : public AActor
{
    GENERATED_BODY()

public:
    virtual void TakeDamage(float Damage, AActor *DamageCauser);
};

UCLASS()
class BACKROWSTUDIO_API AEnemy : public ADamageActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AEnemy();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    virtual void TakeDamage(float Damage, AActor *DamageCauser) override;
};
