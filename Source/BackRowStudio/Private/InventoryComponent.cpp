#include "InventoryComponent.h"

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

void UInventoryComponent::BeginPlay()
{
    Items.SetNum(NumberOfInventorySlots, false);
    Spells.SetNum(4, false);
    Super::BeginPlay();
}


void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) { Super::TickComponent(DeltaTime, TickType, ThisTickFunction); }
