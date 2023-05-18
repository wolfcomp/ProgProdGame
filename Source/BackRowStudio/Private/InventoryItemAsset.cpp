#include "InventoryItemAsset.h"

FSlotStruct::FSlotStruct() { Item = nullptr; }

FSlotStruct::FSlotStruct(UInventoryItemAsset *item, int quantity)
{
    Item = item;
    Quantity = quantity;
}

FSlotStruct::FSlotStruct(int quantity) { Quantity = quantity; }

FSlotStruct::operator bool() const { return Item->IsValidLowLevel() && Quantity > 0; }

FSlotStruct &FSlotStruct::operator+=(FSlotStruct &slot)
{
    if (const int available = this->Item->MaxQuantity - this->Quantity; available > 0 && slot.Item == this->Item)
    {
        if (slot.Quantity >= available)
        {
            slot.Quantity -= available;
            this->Quantity += available;
            return *this;
        }
        this->Quantity += slot.Quantity;
        slot.Quantity = 0;
        return *this;
    }
    return *this;
}

bool operator==(const FSlotStruct &lhs, const FSlotStruct &rhs) { return lhs.Item == rhs.Item && lhs.Quantity == rhs.Quantity; }
