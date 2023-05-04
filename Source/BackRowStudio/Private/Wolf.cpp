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
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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
	if (APawn* tempPawn = GetWorld()->GetFirstPlayerController()->GetPawn(); tempPawn->IsValidLowLevel())
	{
		if (AMainCharacter* temp = Cast<AMainCharacter>(tempPawn); temp->IsValidLowLevel())
		{
			PlayerRef = temp;
		}
	}

	if (AWolfAIController* tempCon = Cast<AWolfAIController>(GetController()))
	{
		WolfAIController = tempCon;
		WolfAIController->Patrol();
	}

	Super::BeginPlay();
}

// Called every frame
void AWolf::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AWolf::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AWolf::TryAttack(AActor* actorToAttack)
{
	MyAnimationState = Attacking;
}

void AWolf::TryStoppingAttack()
{
	MyAnimationState = Moving;
}
