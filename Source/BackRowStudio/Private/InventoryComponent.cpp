// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if(ItemDataTable)
	{
		Items = ItemDataTable;
	    //GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Black,FString(Items->GetRowStructPathName().ToString()));
		GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Black,Items->FindRow<FItemStruct>(FName("NewRow_" + FString::FromInt(0)),"",true)->MyDebugMsg);
		//Items->FindRowUnchecked(FName(*FString::FromInt(1)));
		//MyItem = Items->FindRow<FItemStruct>("1","",true);
	}
    else
    {
		GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Black,FString("something is wrong with the items data table"));
    }
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

