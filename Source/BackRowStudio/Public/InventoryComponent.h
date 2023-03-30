// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "engine/DataTable.h"
#include "Engine/Texture2D.h"
#include "InventoryComponent.generated.h"


USTRUCT(blueprinttype)
struct FItemStruct : public FTableRowBase
{
	GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int MaxQuantity = 64;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* MyImage = LoadObject<UTexture2D>(NULL, TEXT("/Engine/EngineResources/AICON-Red"), NULL, LOAD_None, NULL);
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString MyDebugMsg = "this is a debug msg";
};

USTRUCT(blueprinttype)
struct FSlotStruct
{
    GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemStruct MyItem;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Quantity;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BACKROWSTUDIO_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UDataTable* ItemDataTable = nullptr;
	UDataTable* Items;
	FItemStruct* MyItem;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
