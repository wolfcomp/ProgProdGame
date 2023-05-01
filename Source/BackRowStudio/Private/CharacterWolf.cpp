// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterWolf.h"

// Sets default values
ACharacterWolf::ACharacterWolf()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Value = 100;
}

// Called when the game starts or when spawned
void ACharacterWolf::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacterWolf::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterWolf::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

