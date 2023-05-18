#include "InventoryWidget.h"
#include "InventoryComponent.h"
#include "SlotWidget.h"

void UInventoryWidget::NativeConstruct() { Super::NativeConstruct(); }

void UInventoryWidget::UpdateInventory()
{
    if (Inventory->IsValidLowLevel() && SlotWidget != nullptr)
    {
        BagPanel->ClearChildren();
        SpellPanel->ClearChildren();
        if (!Inventory->Items.IsEmpty())
        {
            for (int i = 0; i < Inventory->Items.Num(); ++i)
            {
                auto *slotWidget = CreateWidget<USlotWidget>(this, SlotWidget);
                slotWidget->InventoryWidget = this;
                slotWidget->MyContent = Inventory->Items[i];
                BagPanel->AddChildToGrid(slotWidget, i / HorizontalLimit, i % HorizontalLimit);
            }
        }

        if (!Inventory->Spells.IsEmpty())
        {
            for (int i = 0; i < Inventory->Spells.Num(); ++i)
            {
                auto *slotWidget = CreateWidget<USlotWidget>(this, SlotWidget);
                slotWidget->InventoryWidget = this;
                slotWidget->MyContent = Inventory->Spells[i];
                SpellPanel->AddChildToGrid(slotWidget, i / HorizontalLimit, i % HorizontalLimit);
            }
        }
    }
}
