// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"

#include "SlotWidget.h"

void UInventoryWidget::NativeTick(const FGeometry &MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
}

void UInventoryWidget::NativePreConstruct()
{
    //MySlotW = *Cast<TSubclassOf<USlotWidget>>(MySlotWidget);
    //temp = Cast<USlotWidget, UUserWidget>(MySlotWidget);
    //MySlotW = TCastImpl<USlotWidget, TSubclassOf<USlotWidget>, ECastType::UObjectToUObject>();
    //TCastImpl<TSubclassOf<UUserWidget>,TSubclassOf<USlotWidget>,ECastType::UObjectToUObject>(MySlotWidget);
    //TCastImpl<From,To,ECastType::UObjectToUObject>::DoCast(UObject *)
    //MySlotWidget = *LoadObject<TSubclassOf<USlotWidget>>(nullptr, TEXT(""), nullptr, LOAD_None, nullptr);
    //C:/Users/Dennis/Documents/Unreal Projects/ProgProdGame/Content/IndividualFolders/Dennis/BP_InventoryWidget.uasset
    if(!MyInventory.IsEmpty() && MySlotWidget != __nullptr)
    {
        MyInv = MyInventory;
        for (int i = 0; i < MyInventory.Num(); ++i)
        {
            UUserWidget* t = CreateWidget(this, MySlotWidget,FName(*FString("a")+i));
            USlotWidget* a = Cast<USlotWidget>(t);
            a->MyContent = MyInventory[i];
            MyHorizontal->AddChildToHorizontalBox(a);
        }
    }
    else
    {
        if(MyInventory.IsEmpty())
        {
            GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Black,FString("InventoryWidgets inventory is empty"));
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Black,FString("InventoryWidgets slotWidget is nullptr"));
            if (MySlotWidget != nullptr)
            {
                GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Yellow,MySlotWidget->GetClass()->GetName());
            }
        }
    }
    Super::NativePreConstruct();
}

