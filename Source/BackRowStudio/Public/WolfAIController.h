// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "WolfAIController.generated.h"

//REALLY helpful tutorial https://www.youtube.com/watch?v=DwjehZh5YQ0&t=119s
/**
 * 
 */
UCLASS()
class BACKROWSTUDIO_API AWolfAIController : public AAIController
{
	GENERATED_BODY()
protected:
    virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	APawn* PlayerPawn;

	class AWolf* controlledWolf;

	class UNavigationSystemV1* NavArea;

	FVector RandomLocation = FVector();

	bool bMoveToPlayer;
	bool bSearchForPlayer;
	bool bCanAttackPlayer;

	float wolfStoppingDistance = 60.0f;
	float wolfAttackDistance = 200.0f;

	void GenerateRandomSearchLocation();
	void SearchForPlayer();

	void MoveToPlayer();
	void StartChasingPlayer();
	bool IsWolfCloseToPlayer();
	void AttackPlayer();

	FTimerHandle SearchTimerHandle;
	FTimerHandle AttackTimerHandle;

public:
    virtual void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result) override;

	UFUNCTION()
	void OnDetectPlayerBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnDetectPlayerEndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);


};
