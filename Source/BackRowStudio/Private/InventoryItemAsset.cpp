// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItemAsset.h"

FSlotStruct::FSlotStruct() { Item = nullptr; }

void FSlotStruct::Erase()
{
    Item = nullptr;
    Quantity = NULL;
}

FSlotStruct::FSlotStruct(UInventoryItemAsset *InItem, int InQuantity)
{
    Item = InItem;
    Quantity = InQuantity;
}

FSlotStruct::FSlotStruct(int InQuantity) { Quantity = InQuantity; }

FSlotStruct::operator bool() const { return Item->IsValidLowLevel() && Quantity > 0; }

FSlotStruct &FSlotStruct::operator+=(FSlotStruct &inSlot)
{
    if (const int available = this->Item->MaxQuantity - this->Quantity; available > 0 && inSlot.Item == this->Item)
    {
        if (inSlot.Quantity >= available)
        {
            inSlot.Quantity -= available;
            this->Quantity += available;
            return *this;
        }
        this->Quantity += inSlot.Quantity;
        inSlot.Quantity = 0;
        return *this;
    }
    return *this;
}

bool operator==(const FSlotStruct &lhs, const FSlotStruct &rhs) { return lhs.Item == rhs.Item && lhs.Quantity == rhs.Quantity; }
