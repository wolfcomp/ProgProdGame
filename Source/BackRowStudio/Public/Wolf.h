// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "PatrolPathActor.h"
#include "Wolf.generated.h"

// https://awesometuts.com/blog/unreal-engine-enemy-ai/

UENUM(BlueprintType)
enum WolfAnimationType
{
    Stopped UMETA(DisplayName = "Stopped"),
    Moving UMETA(DisplayName = "Moving"),
    Attacking UMETA(DisplayName = "Attacking"),
};

UCLASS()
class BACKROWSTUDIO_API AWolf : public ADamageActor
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    AWolf();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    UPROPERTY(EditAnywhere, Category="Wolf")
    int AttackPower = 100;

    UPROPERTY(EditAnywhere, Category="Wolf")
    int Health = 500;

    UPROPERTY(VisibleAnywhere)
    class AMainCharacter *PlayerRef;

    UPROPERTY(VisibleAnywhere)
    class AWolfAIController *WolfAIController;

    UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Artist")
    bool Patrol;

    UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Artist")
    bool MoveToPlayer;

    UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Artist", meta=(EditCondition="Patrol==true", EditConditionHides))
    TObjectPtr<APatrolPathActor> PatrolPath = ArtistUtility();


    UPROPERTY()
    float PlayerAttackCollisionDetectionRadius = 320;

    UPROPERTY()
    float PlayerForgetRadius = 1280;

    UPROPERTY(EditAnywhere)
    class UBoxComponent *AttackHitBox;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TEnumAsByte<WolfAnimationType> MyAnimationState = WolfAnimationType::Moving;

    UFUNCTION()
    void TryAttack(AActor *actor_to_attack);

    UFUNCTION()
    void TryStoppingAttack();

    void HideActor(bool is_hidden);

    virtual void TakeDamage(int, AActor *) override;


    TObjectPtr<APatrolPathActor> ArtistUtility();
};
