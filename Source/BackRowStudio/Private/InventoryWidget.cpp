// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "InventoryComponent.h"

void UInventoryWidget::NativeTick(const FGeometry &geometry, float delta_time) { Super::NativeTick(geometry, delta_time); }

void UInventoryWidget::NativePreConstruct() { Super::NativePreConstruct(); }

void UInventoryWidget::NativeConstruct()
{
    if(Inventory->IsValidLowLevel())
    {
        if (!Inventory->Items.IsEmpty())
        {
            if (SlotWidget != nullptr)
            {
                for (int i = 0; i < Inventory->Items.Num(); ++i)
                {
                    auto *slotWidget = Cast<USlotWidget>(CreateWidget(this, SlotWidget));
                    slotWidget->MyContent = Inventory->Items[i];
                    BagPanel->AddChildToGrid(slotWidget, i / HorizontalLimit, i % HorizontalLimit);
                }
            }
        }
        if(!Inventory->Spells.IsEmpty())
        {
            if(SlotWidget != nullptr)
            {
                for(int i = 0; i < Inventory->Spells.Num(); ++i)
                {
                    auto *slotWidget = Cast<USlotWidget>(CreateWidget(this, SlotWidget));
                    slotWidget->MyContent = Inventory->Spells[i];
                    SpellPanel->AddChildToGrid(slotWidget, i / HorizontalLimit, i % HorizontalLimit);
                }
            }
        }
    }
    Super::NativeConstruct();
}