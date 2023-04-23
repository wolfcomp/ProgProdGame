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

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
    TArray<FSlotStruct> Items;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
    TArray<FSlotStruct> Spells;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int NumberOfInventorySlots = 15;

	UFUNCTION(BlueprintCallable)
    bool AddItem(FSlotStruct item);

	UFUNCTION(BlueprintCallable)
    bool AddSpell(FSlotStruct spell);

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
};