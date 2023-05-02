// Fill out your copyright notice in the Description page of Project Settings.


#include "Wolf.h"

#include "Animation/AnimMontage.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SplineComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MainCharacter.h"
#include "WolfAIController.h"

// Sets default values
AWolf::AWolf()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PlayerDetected = false;

	PlayerAttackCollisionDetection = CreateDefaultSubobject<USphereComponent>(TEXT("Attempt Attack Range Visual"));
	PlayerAttackCollisionDetection->SetupAttachment(RootComponent);
	PlayerAttackCollisionDetection->SetCollisionResponseToAllChannels(ECR_Ignore);

	PlayerAutoSpotRadius = CreateDefaultSubobject<USphereComponent>(TEXT("spot player Range Visual"));
	PlayerAutoSpotRadius->SetupAttachment(RootComponent);
	PlayerAutoSpotRadius->SetCollisionResponseToAllChannels(ECR_Ignore);

	PlayerForgetRadius = CreateDefaultSubobject<USphereComponent>(TEXT("forget player Range Visual"));
	PlayerAutoSpotRadius->SetupAttachment(RootComponent);
	PlayerAutoSpotRadius->SetCollisionResponseToAllChannels(ECR_Ignore);

	PatrolPath = CreateDefaultSubobject<USplineComponent>(TEXT("Wolf Patrol Path"));
	PatrolPath->SetupAttachment(RootComponent);

	AttackHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Wolf Attack Hitbox"));
	AttackHitBox->SetupAttachment(RootComponent);

	// setting up character movement
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

// Called when the game starts or when spawned
void AWolf::BeginPlay()
{
	if (AWolfAIController* tempCon = Cast<AWolfAIController>(GetController()))
	{
		WolfAIController = tempCon;
		UsingWolfController = true;
	}
	if (APawn* tempPawn = GetWorld()->GetFirstPlayerController()->GetPawn(); tempPawn->IsValidLowLevel())
	{
		if (AMainCharacter* temp = Cast<AMainCharacter>(tempPawn); temp->IsValidLowLevel())
		{
			PlayerRef = temp;
		}
	}

	AnimInstance = GetMesh()->GetAnimInstance();

	Super::BeginPlay();
}

// Called every frame
void AWolf::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PlayerRef->IsValidLowLevel())
	{
		if (const double distance = FVector::Dist(PlayerRef->GetActorLocation(), GetActorLocation()); distance <=
			PlayerAutoSpotRadius->GetScaledSphereRadius())
		{
			PlayerDetected = true;
			if (distance <= PlayerAttackCollisionDetection->GetScaledSphereRadius())
			{
				if (WolfAIController->IsValidLowLevel())
				{
					WolfAIController->Deactivate();
				}
				TryAttack(PlayerRef);
			}
		}
		else if (distance >= PlayerForgetRadius->GetScaledSphereRadius())
		{
			PlayerDetected = false;
		}
	}
}

// Called to bind functionality to input
void AWolf::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AWolf::TryAttack(AActor* actorToAttack)
{
	if (AttackMontage)
	{
		AnimInstance->Montage_Play(AttackMontage);
	}
}

void AWolf::AttackAnimationEnded()
{
	if (UsingWolfController)
	{
		WolfAIController->Reactivate();
	}
}

void AWolf::AttackAnimationBegin()
{
	if (UsingWolfController)
	{
		WolfAIController->Deactivate();
	}
}

void AWolf::AttackingFramesBegin()
{
	if (UsingWolfController)
	{
		IsAttackingFrame = true;
	}
}

void AWolf::AttackingFramesEnd()
{
	if (UsingWolfController)
	{
		IsAttackingFrame = false;
	}
}
