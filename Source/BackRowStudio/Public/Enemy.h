// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class ADamageActor : public AActor
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float) override;

    virtual void TakeDamage(int, AActor *);
};

UCLASS()
class BACKROWSTUDIO_API AEnemy : public ADamageActor
{
    GENERATED_BODY()

public:
    AEnemy();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float) override;

    virtual void TakeDamage(int, AActor *) override;
};
