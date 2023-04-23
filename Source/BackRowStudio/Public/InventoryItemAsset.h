// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/Texture2D.h"
#include "SpellActor.h"
#include "InventoryItemAsset.generated.h"


UCLASS(BlueprintType)
class BACKROWSTUDIO_API UInventoryItemAsset : public UDataAsset
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int MaxQuantity = 64;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UTexture2D *MyImage = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FString MyDebugMsg = "this is a debug msg";

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    bool HasMenu = true;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    bool HasDropMenu = true;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    bool HasUseMenu = false;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    bool HasEquipMenu = false;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    USpell* Spell;
};

USTRUCT(blueprinttype)
struct FSlotStruct
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UInventoryItemAsset *Item = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int Quantity = 0;

    FSlotStruct();

    //void Erase();

    explicit FSlotStruct(UInventoryItemAsset *item, int quantity);

    explicit FSlotStruct(int quantity);

    explicit operator bool() const;

    FSlotStruct &operator+=(FSlotStruct &a);

    friend bool operator==(const FSlotStruct &lhs, const FSlotStruct &rhs);
};