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
	//WolfAiBlackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Wolf Blackboard Component"));
	//WolfAiBehaviorTree = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
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
		//WolfAIController->GetPathFollowingComponent()->OnRequestFinished.AddUObject
	 //   (this, &AWolf::OnMoveCompleted);
	}

	AnimInstance = GetMesh()->GetAnimInstance();
	AttackHitBox->OnComponentBeginOverlap.AddDynamic(this, &AWolf::OnAttackHitBoxBeginOverlap);

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
	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, TEXT("I just finished moving today"));
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

void AWolf::OnAttackHitBoxBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	PlayerRef = Cast<AMainCharacter>(OtherActor);
	if (PlayerRef && CanDealDamage)
	{
		// deal damage to player
		UE_LOG(LogTemp, Warning, TEXT("Player Damaged"));
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, TEXT("Insert 3 paragraph evil monologue here"));
	}
}

