// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryComponent.h"
#include "InventoryWidget.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent() { PrimaryComponentTick.bCanEverTick = true; }

bool UInventoryComponent::AddItem(FSlotStruct item)
{
    for (auto &itemSlot : Items)
    {
        if (itemSlot.Item == item.Item)
        {
            itemSlot.Quantity += item.Quantity;
            return true;
        }
        if (itemSlot.Item == nullptr)
        {
            itemSlot = item;
            return true;
        }
    }
    return false;
}

bool UInventoryComponent::AddSpell(FSlotStruct spell)
{
    for (auto &spellItem : Spells)
    {
        if (spellItem.Item == spell.Item)
        {
            spellItem.Quantity += spell.Quantity;
            return true;
        }
        if (spellItem.Item == nullptr)
        {
            spellItem = spell;
            return true;
        }
    }
    return false;
}

// void UInventoryComponent::DisplayInventory()
//{
//     TArray<FSlotStruct>* localInvShortHand = &Inventory;
//	if (!localInvShortHand)
//	{
//	    GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red,"This Inventory Component's Inventory Is Not Valid");
//	}
//	else if (!MyInvWidget)
//     {
//         GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red,"My Inventory Widget Is Not Valid");
//     }
//	else if (MyInvWidget && localInvShortHand)
//	{
//		GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red,"Got Here");
//         //InvWidget = CreateWidget<UInventoryWidget>(GetWorld(), MyInvWidget, FName("Minimap"));
//         //InvWidget->Inventory = this;
//         //InvWidget->AddToViewport();
//	}
// }
//
// void UInventoryComponent::CloseInventory()
//{
//	InvWidget->RemoveFromParent();
// }

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
