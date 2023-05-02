// Fill out your copyright notice in the Description page of Project Settings.


#include "Wolf.h"

#include "Animation/AnimMontage.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
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
	PlayerDetected = false;

	//PlayerAttackCollisionDetection = CreateDefaultSubobject<USphereComponent>(TEXT("Attempt Attack Range Visual"));
	//PlayerAutoSpotRadius = CreateDefaultSubobject<USphereComponent>(TEXT("spot player Range Visual"));
	//PlayerForgetRadius = CreateDefaultSubobject<USphereComponent>(TEXT("forget player Range Visual"));
	PatrolPath = CreateDefaultSubobject<USplineComponent>(TEXT("Wolf Patrol Path"));
	AttackHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Wolf Attack Hitbox"));

	//PlayerAttackCollisionDetection->SetupAttachment(RootComponent);
	//PlayerAutoSpotRadius->SetupAttachment(RootComponent);
	//PlayerAutoSpotRadius->SetupAttachment(RootComponent);
	PatrolPath->SetupAttachment(RootComponent);
	AttackHitBox->SetupAttachment(RootComponent);

	//PlayerAttackCollisionDetection->SetCollisionResponseToAllChannels(ECR_Ignore);
	//PlayerAutoSpotRadius->SetCollisionResponseToAllChannels(ECR_Ignore);
	//PlayerAutoSpotRadius->SetCollisionResponseToAllChannels(ECR_Ignore);

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
	//CurrentSpotRadius = PlayerAutoSpotRadius->GetScaledSphereRadius();

	Super::BeginPlay();
	//FDateTime a = FDateTime::Now;
	if (!AttackMontage->IsValidLowLevel())
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("something wrong here"));
	}
}

// Called every frame
void AWolf::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Green, FString::FromInt(GetWorld()->TimeSeconds));
	//GEngine->AddOnScreenDebugMessage(2, 3.f, FColor::Green, FString::FromInt(WolfAIController->playerMoveTimeTilNextCheck));
	if (PlayerRef->IsValidLowLevel())
	{
		if (const double distance = FVector::Dist(PlayerRef->GetActorLocation(), GetActorLocation()); distance <=
			CurrentSpotRadius && WolfAIController->IsValidLowLevel())
		{
			if (distance <= PlayerAttackCollisionDetectionRadius && PlayerDetected)
			{
				TryAttack(PlayerRef);
			}
			else if (!PlayerDetected)
			{
				WolfAIController->MoveToPlayer();
				//DrawDebugSphere(GetWorld(), GetNavAgentLocation(), PlayerForgetRadius, 16, FColor::Red, true, 10);
			}
			else
			{
				WolfAIController->MoveToPlayer();
			}
			PlayerDetected = true;
			CurrentSpotRadius = PlayerForgetRadius;
		}
		else
		{
			CurrentSpotRadius = PlayerAutoSpotRadius;
			PlayerDetected = false;
			if (FVector::Dist(WolfAIController->patrolPoints[CurrentPatrolPoint], this->GetNavAgentLocation()) < 100)
			{
				if (CurrentPatrolPoint + 1 >= WolfAIController->patrolPoints.Num())
				{
					CurrentPatrolPoint = 0;
				}
				else
				{
					CurrentPatrolPoint++;
				}
			}
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
	if (AttackMontage && GetMesh()->GetAnimInstance()->IsValidLowLevel())
	{
		GetMesh()->GetAnimInstance()->Montage_Play(AttackMontage);
		//FTimerHandle timerHandle;
		//GetWorld()->GetTimerManager().SetTimer(timerHandle, [&]()
		//{
		//	UE_LOG(LogTemp, Warning, TEXT("This text will appear in the console 3 seconds after execution"))
		//}, 3, false);
	}
}

void AWolf::AttackAnimationEnded()
{
	if (WolfAIController->IsValidLowLevel())
	{
		WolfAIController->Reactivate();
	}
}

void AWolf::AttackAnimationBegin()
{
	if (WolfAIController->IsValidLowLevel())
	{
		WolfAIController->Deactivate();
	}
}

void AWolf::AttackingFramesBegin()
{
	if (WolfAIController->IsValidLowLevel())
	{
		IsAttackingFrame = true;
	}
}

void AWolf::AttackingFramesEnd()
{
	if (WolfAIController->IsValidLowLevel())
	{
		IsAttackingFrame = false;
	}
}
