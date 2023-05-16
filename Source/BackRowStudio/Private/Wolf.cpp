// Fill out your copyright notice in the Description page of Project Settings.


#include "Wolf.h"

#include "Animation/AnimMontage.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Async/Future.h"
#include "MainCharacter.h"
#include "WolfAIController.h"
#include "Components/SplineComponent.h"

// Sets default values
AWolf::AWolf()
{
    Patrol = true;

    PrimaryActorTick.bCanEverTick = true;
    AttackHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Wolf Attack Hitbox"));
    AttackHitBox->SetupAttachment(RootComponent);

    // setting up character movement
    GetCharacterMovement()->MaxWalkSpeed = 600.0f;
    GetCharacterMovement()->bOrientRotationToMovement = true;
    AIControllerClass = AWolfAIController::StaticClass();
    SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
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
    if (Controller == nullptr)
    {
        this->SpawnDefaultController();
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

TObjectPtr<APatrolPathActor> AWolf::ArtistUtility()
{
    float smallestDistance = INFINITY;
    TObjectPtr<APatrolPathActor> returnActor;
    TArray<AActor *> actors;
    UGameplayStatics::GetAllActorsOfClass(this, APatrolPathActor::StaticClass(), actors);
    if (actors.IsValidIndex(0))
    {
        for (int i = 0; i < actors.Num(); ++i)
        {
            APatrolPathActor *actor = Cast<APatrolPathActor>(actors[i]);
            for (int i2 = 0; i2 < actor->PatrolPath->GetNumberOfSplinePoints(); ++i2)
            {
                if (const float distance = FVector::Dist(GetActorLocation(), actor->PatrolPath->GetWorldLocationAtSplinePoint(i2)); distance < smallestDistance)
                {
                    smallestDistance = distance;
                    returnActor = ToObjectPtr(actor);
                }
            }
        }
    }
    else
    {
        Patrol = false;
    }

    return returnActor;
}
