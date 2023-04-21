// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryComponent.h"
#include "InventoryWidget.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent() { PrimaryComponentTick.bCanEverTick = true; }

void UInventoryComponent::AddItem(FSlotStruct item)
{
    for (auto &itemSlot : Items)
    {
        if (itemSlot.Item == item.Item)
        {
            itemSlot.Quantity += item.Quantity;
            return;
        }
        if (itemSlot.Item == nullptr)
        {
            itemSlot = item;
            return;
        }
    }
}

void UInventoryComponent::AddSpell(FSlotStruct spell)
{
    for (auto &spellItem : Spells)
    {
        if (spellItem.Item == spell.Item)
        {
            spellItem.Quantity += spell.Quantity;
            return;
        }
        if (spellItem.Item == nullptr)
        {
            spellItem = spell;
            return;
        }
    }
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
    Items.SetNum(NumberOfInventorySlots, false);
    Spells.SetNum(4, false);
    Super::BeginPlay();
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
}
