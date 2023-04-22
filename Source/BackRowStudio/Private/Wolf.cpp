// Fill out your copyright notice in the Description page of Project Settings.


#include "Wolf.h"

#include "Components/SphereComponent.h"

// Sets default values
AWolf::AWolf()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DetectPlayerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Detect Player Sphere"));
	DetectPlayerSphere->SetupAttachment(RootComponent);
	PatrolPath = CreateDefaultSubobject<USplineComponent>(TEXT("Wolf Patrol Path"));
	PatrolPath->SetupAttachment(RootComponent);
	//this->AIControllerClass = AWolfAIController
}

// Called when the game starts or when spawned
void AWolf::BeginPlay()
{
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

