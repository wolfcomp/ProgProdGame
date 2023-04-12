// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Components/ActorComponent.h"
#include "Engine/Texture2D.h"
#include "InventoryItemAsset.generated.h"


UCLASS(BlueprintType)
class BACKROWSTUDIO_API UInventoryItemAsset : public UDataAsset
{
	GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere,BlueprintReadOnly)
	    int MaxQuantity = 64;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	    TSoftObjectPtr<UTexture2D> MyImage = TSoftObjectPtr<UTexture2D>(FSoftObjectPath("/Script/Engine.Texture2D'/Game/IndividualFolders/Dennis/womanyellingcat-1573233850.womanyellingcat-1573233850'"));
    UPROPERTY(EditAnywhere,BlueprintReadOnly)
	    FString MyDebugMsg = "this is a debug msg";
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	    bool HasMenu = true;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	    bool HasDropMenu = true;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	    bool HasUseMenu = false;
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	    bool HasEquipMenu = false;
};

USTRUCT(blueprinttype)
struct FSlotStruct
{
    GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	    TSoftObjectPtr<UInventoryItemAsset> Item = TSoftObjectPtr<UInventoryItemAsset>(FSoftObjectPath("/Script/BackRowStudio.InventoryItemAsset'/Game/IndividualFolders/Dennis/Items/FallBackItem.FallBackItem'"));
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	    int Quantity = 0;

	FSlotStruct();

    void Erase();

	explicit FSlotStruct(UInventoryItemAsset* InItem, int InQuantity);
	explicit FSlotStruct(int InQuantity);

    explicit operator bool() const;
	FSlotStruct& operator+= (FSlotStruct& a);
    friend bool operator==(const FSlotStruct & lhs, const FSlotStruct & rhs);
};