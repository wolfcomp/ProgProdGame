// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

void ADamageActor::TakeDamage(float Damage, AActor *DamageCauser)
{
	//Implement in sub actors
}

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy::TakeDamage(float Damage, AActor *DamageCauser)
{
    
}
