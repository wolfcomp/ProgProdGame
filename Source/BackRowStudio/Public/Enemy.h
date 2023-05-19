#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class ADamageActor : public ACharacter
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float) override;

    UFUNCTION(BlueprintCallable)
    virtual void TakeDamage(int damage, AActor *actor);
};

UCLASS()
class BACKROWSTUDIO_API AEnemy : public ADamageActor
{
    GENERATED_BODY()

public:
    AEnemy();

    UPROPERTY(EditAnywhere, Category = "Mesh")
    UStaticMeshComponent *StaticMesh;

    UPROPERTY(EditAnywhere, Category = "Damage")
    int AttackPower = 100;

    UPROPERTY(EditAnywhere, Category = "Damage")
    int Health = 500;

    UPROPERTY(EditAnywhere, Category = "Damage")
    float PushForce = 1;

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float) override;

    virtual void TakeDamage(int, AActor *) override;
};
