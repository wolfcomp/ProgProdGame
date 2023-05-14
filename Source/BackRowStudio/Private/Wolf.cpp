// Fill out your copyright notice in the Description page of Project Settings.


#include "Wolf.h"

#include "Animation/AnimMontage.h"
#include "Components/BoxComponent.h"
#include "Components/SplineComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Async/Future.h"
#include "MainCharacter.h"
#include "WolfAIController.h"

// Sets default values
AWolf::AWolf()
{
    PrimaryActorTick.bCanEverTick = true;

    PatrolPath = CreateDefaultSubobject<USplineComponent>(TEXT("Wolf Patrol Path"));
    AttackHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Wolf Attack Hitbox"));

    PatrolPath->SetupAttachment(RootComponent);
    AttackHitBox->SetupAttachment(RootComponent);

    // setting up character movement
    GetCharacterMovement()->MaxWalkSpeed = 600.0f;
    GetCharacterMovement()->bOrientRotationToMovement = true;
}

// Called when the game starts or when spawned
void AWolf::BeginPlay()
{
    if (APawn *tempPawn = GetWorld()->GetFirstPlayerController()->GetPawn(); tempPawn->IsValidLowLevel())
    {
        if (AMainCharacter *temp = Cast<AMainCharacter>(tempPawn); temp->IsValidLowLevel())
        {
            PlayerRef = temp;
        }
    }

    if (AWolfAIController *tempCon = Cast<AWolfAIController>(GetController()))
    {
        WolfAIController = tempCon;
        WolfAIController->Patrol();
    }

    Super::BeginPlay();
}

void AWolf::TryAttack(AActor *actor_to_attack)
{
    MyAnimationState = Attacking;
}

void AWolf::TryStoppingAttack()
{
    MyAnimationState = Moving;
}

void AWolf::HideActor(bool is_hidden)
{
    SetActorHiddenInGame(!is_hidden);
    SetActorEnableCollision(is_hidden);
    SetActorTickEnabled(is_hidden);
    MyAnimationState = Moving;
}

void AWolf::TakeDamage(int i, AActor *actor)
{
    Super::TakeDamage(i, actor);
    Health -= i;

    if (Health < 0)
    {
        HideActor(true);
    }
}
