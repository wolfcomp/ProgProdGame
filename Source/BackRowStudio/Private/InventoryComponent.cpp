// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryComponent.h"
#include "InventoryWidget.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent() { PrimaryComponentTick.bCanEverTick = true; }

void UInventoryComponent::AddToInventory(TArray<FSlotStruct> content)
{
    TArray<FSlotStruct> content2 = content;
    TArray<FSlotStruct> toRemove;
    ;
    for (auto &myContent : Inventory)
    {
        for (auto inContent : content2)
        {
            if (inContent.Item->IsValidLowLevel() == false || inContent.Quantity == 0)
            {
                toRemove.Add(inContent);
                GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "got here 0");
            }
            else if (myContent.Quantity == 0 || myContent.Item->IsValidLowLevel() == false)
            {
                GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "got here 0.5");
                myContent = inContent;
                toRemove.Add(inContent);
            }
            else if (inContent.Item == myContent.Item)
            {
                if (myContent.Quantity + inContent.Quantity <= myContent.Item->MaxQuantity)
                {
                    myContent.Quantity += inContent.Quantity;
                    toRemove.Add(inContent);
                    GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "got here 1");
                }
                else
                {
                    if (const int remaining = myContent.Quantity + inContent.Quantity - myContent.Item->MaxQuantity; remaining > 0)
                    {
                        GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "got here 2");
                    }
                }
            }
        }
        for (FSlotStruct remove : toRemove)
        {
            content2.Remove(remove);
        }
    }
}

void UInventoryComponent::PickUpFunction(UInventoryComponent *collisionInventory)
{
    if (collisionInventory->IsValidLowLevel() && collisionInventory != this)
    {
        if (PicksUpOrPickup == true)
        {
            AddToInventory(collisionInventory->Inventory);
            collisionInventory->PickUpFunction(this);
        }
        else
        {
            this->GetOwner()->Destroy();
            // GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red,"destroyed");
        }
    }
}

//void UInventoryComponent::DisplayInventory()
//{
//    TArray<FSlotStruct>* localInvShortHand = &Inventory;
//	if (!localInvShortHand)
//	{
//	    GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red,"This Inventory Component's Inventory Is Not Valid");
//	}
//	else if (!MyInvWidget)
//    {
//        GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red,"My Inventory Widget Is Not Valid");
//    }
//	else if (MyInvWidget && localInvShortHand)
//	{
//		GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red,"Got Here");
//        //InvWidget = CreateWidget<UInventoryWidget>(GetWorld(), MyInvWidget, FName("Minimap"));
//        //InvWidget->Inventory = this;
//        //InvWidget->AddToViewport();
//	}
//}
//
//void UInventoryComponent::CloseInventory()
//{
//	InvWidget->RemoveFromParent();
//}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
    if (!MyInventory.IsEmpty())
    {
        Inventory = MyInventory;
        Inventory.SetNum(NumberOfInventorySlots, false);
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "Invalid Inventory");
    }
    Super::BeginPlay();
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
}
