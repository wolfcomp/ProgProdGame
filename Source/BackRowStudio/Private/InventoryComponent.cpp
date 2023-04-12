// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryComponent.h"
//#include "InventoryWidget.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

UInventoryComponent * UInventoryComponent::operator*(UInventoryComponent in)
{
	return this;
}

void UInventoryComponent::AddToInventory(TArray<FSlotStruct> content)
{
	//if(!content.IsEmpty())
	//{
	//	for(int i = 0; i < Inventory.Num(); ++i)
	//	{
	//	    
	//	}
	//	for (int i = 0; i < content.Num(); ++i)
 //       {
	//	    if(content[i].Item->GetFName().IsValid() && content[i].Item != ItemForEmptySlot)
	//        {
 //               for (int i2 = 0; i2 < Inventory.Num(); ++i2)
 //               {
	//		        if(content[i].Quantity <= 0)
	//		        {
	//		            return;
	//		        }
 //                   if(Inventory[i2].Item == ItemForEmptySlot)
 //                   {
 //                       Inventory[i2] = content[i];
 //                       return;
 //                   }
	//		        if(const int available = Inventory[i2].Item->MaxQuantity - Inventory[i2].Quantity; available > 0 && Inventory[i2].Item == content[i].Item)
	//		        {
	//			        if(content[i].Quantity >= available)
	//			        {
	//				        content[i].Quantity -= available;
	//				        Inventory[i2].Quantity += available;
	//			        }
 //                       else
 //                       {
	//				        Inventory[i2].Quantity += content[i].Quantity;
	//				        return;
 //                       }
	//		        }
 //               }
	//        }
 //       }
	//}
 //   else
 //   {
 //       GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red,"You're Trying To Add An Empty Inventory To Another... Baka!");
 //   }
}

void UInventoryComponent::TestFunction()
{
	if(Inventory.IsValidIndex(0) && Inventory.IsValidIndex(1))
	{
	    Inventory[0] += Inventory[1];
	}
}

//void UInventoryComponent::ConstructInventoryWidget(APlayerController* player_controller) const
//{
//	if(MyInventoryWidget->IsValidLowLevel())
//	{
//		if(UInventoryWidget *a = Cast<UInventoryWidget>(MyInventoryWidget))
//		{
//		    a->AddToViewport();
//			UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(player_controller,a);
//		}
//        else
//        {
//            GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red,"Inventory Widget not subclass of UUSerWidget somehow");   
//        }
//	}
//    else
//    {
//        GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red,"MyInventoryWidget is not valid");
//    }
//	UUserWidget* returnObj = nullptr;;
//}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	if(!MyInventory.IsEmpty())
	{
	    Inventory = MyInventory;
        Inventory.SetNum(NumberOfInventorySlots, false);
	}
    else
    {
        GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red,"Invalid Inventory");
    }
    Super::BeginPlay();
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

