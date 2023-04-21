// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotWidget.h"

FSlotStruct USlotWidget::AddContent(USlotWidget *InWidget)
{
    FSlotStruct inContent = InWidget->MyContent;
    if (InWidget != this && inContent.Item->IsValidLowLevel() && inContent.Quantity > 0)
    {
        if (MyContent.Quantity == 0 && inContent.Quantity != 0)
        {
            MyContent = inContent;
            inContent = FSlotStruct();
        }
        else if (inContent.Item == MyContent.Item)
        {
            if (MyContent.Quantity + inContent.Quantity <= MyContent.Item->MaxQuantity)
            {
                MyContent.Quantity += inContent.Quantity;
                inContent = FSlotStruct();
            }
            else
            {
                if (const int remaining = MyContent.Quantity + inContent.Quantity - MyContent.Item->MaxQuantity; remaining > 0)
                {
                    MyContent.Quantity += remaining;
                    inContent.Quantity -= remaining;
                }
            }
        }
    }
    return inContent;
}
