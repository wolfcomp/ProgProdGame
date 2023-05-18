#include "SlotWidget.h"

FSlotStruct USlotWidget::AddContent(USlotWidget *widget)
{
    FSlotStruct content = widget->MyContent;
    if (widget != this && content.Item->IsValidLowLevel() && content.Quantity > 0)
    {
        if (MyContent.Quantity == 0 && content.Quantity != 0)
        {
            MyContent = content;
            content = FSlotStruct();
        }
        else if (content.Item == MyContent.Item)
        {
            if (MyContent.Quantity + content.Quantity <= MyContent.Item->MaxQuantity)
            {
                MyContent.Quantity += content.Quantity;
                content = FSlotStruct();
            }
            else
            {
                if (const int remaining = MyContent.Quantity + content.Quantity - MyContent.Item->MaxQuantity; remaining > 0)
                {
                    MyContent.Quantity += remaining;
                    content.Quantity -= remaining;
                }
            }
        }
    }
    return content;
}
