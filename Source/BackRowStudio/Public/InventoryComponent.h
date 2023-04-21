// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "InventoryItemAsset.h"
#include "InventoryComponent.generated.h"


class UInventoryWidget;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BACKROWSTUDIO_API UInventoryComponent : public UActorComponent
{
    GENERATED_BODY()
public:
    UInventoryComponent();

    UPROPERTY(EditAnywhere, meta = (TitleProperty="Item: {Item} ({Quantity})"))
	TArray<FSlotStruct> MyInventory = {FSlotStruct(10),FSlotStruct(5)};

	UPROPERTY(BlueprintReadWrite)
    TArray<FSlotStruct> Inventory;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool PicksUpOrPickup = true;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int NumberOfInventorySlots = 15;

	UFUNCTION(BlueprintCallable)
	void AddToInventory(TArray<FSlotStruct> content);

	UFUNCTION(BlueprintCallable)
    void PickUpFunction(UInventoryComponent* collisionInventory);

	//UFUNCTION(BlueprintCallable)
	//void DisplayInventory();

	//UFUNCTION(BlueprintCallable)
	//void CloseInventory();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
};