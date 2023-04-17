// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "InventoryComponent.h"

void UInventoryWidget::NativeTick(const FGeometry &MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
}

void UInventoryWidget::NativePreConstruct()
{
    Super::NativePreConstruct();
}

void UInventoryWidget::NativeConstruct()
{
    SlotWidget = MySlotWidget;
    Inventory = MyInventory;
    if(Inventory->IsValidLowLevel())
    {
        if(!Inventory->Inventory.IsEmpty())
        {
            if(SlotWidget != __nullptr)
            {
                int i2 = 0;
                int i3 = 0;
                for (int i = 0; i < Inventory->Inventory.Num(); ++i)
                {
                    if(i % HorizontalLimit == 0)
                    {
                        i2++;
                        i3=0;
                    }
                    USlotWidget *slotWidget = Cast<USlotWidget>(CreateWidget(this, SlotWidget));
                    slotWidget->MyContent = Inventory->Inventory[i];
                    MyGridPanel->AddChildToGrid(slotWidget,i2,i3);
                    i3++;
                }
            }
            else
            {
                GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red,FString("InventoryWidgets slotWidget is nullptr"));
            }
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red,FString("InventoryWidgets inventory is empty"));
        }
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red,FString("InventoryWidgets has that LIVECODING INVENTORY X problem again"));
    }
    Super::NativeConstruct();
}

