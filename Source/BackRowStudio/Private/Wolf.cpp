// Fill out your copyright notice in the Description page of Project Settings.


#include "Wolf.h"

#include "MainCharacter.h"
#include "WolfAIController.h"
#include "Components/SplineComponent.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Animation/AnimMontage.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AWolf::AWolf()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerAttackCollisionDetection = CreateDefaultSubobject<USphereComponent>(TEXT("Attempt Attack Range Visual"));
	PlayerAttackCollisionDetection->SetupAttachment(RootComponent);
	PatrolPath = CreateDefaultSubobject<USplineComponent>(TEXT("Wolf Patrol Path"));
	PatrolPath->SetupAttachment(RootComponent);
	AttackHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Wolf Attack Hitbox"));
	AttackHitBox->SetupAttachment(RootComponent);

	//setting up character movement
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	GetCharacterMovement()->bOrientRotationToMovement = true;

}

// Called when the game starts or when spawned
void AWolf::BeginPlay()
{
	if(AWolfAIController *tempCon = Cast<AWolfAIController>(GetController()))
	{
	    WolfAIController = tempCon;
	}

	AnimInstance = GetMesh()->GetAnimInstance();

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

//just in case we wanna do something like play an animation
void AWolf::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult &Result)
{
}

void AWolf::AttackAnimationEnded()
{
	WolfAIController->Reactivate();
}

void AWolf::TryAttack(AActor *actorToAttack)
{
	if(AttackMontage)
	{
	    AnimInstance->Montage_Play(AttackMontage);   
	}
}

