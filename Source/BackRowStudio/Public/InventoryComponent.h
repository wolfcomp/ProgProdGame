// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryItemAsset.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BACKROWSTUDIO_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()
public:
    UInventoryComponent();
	//don't know why i have define the pointer for this class to prevent the engine from crashing on compile
    UInventoryComponent* operator*(UInventoryComponent in);

    UPROPERTY(EditAnywhere, meta = (TitleProperty="Item: {Item} ({Quantity})", ShowOnlyInnerProperties=true))
	    TArray<FSlotStruct> MyInventory = {FSlotStruct(10),FSlotStruct(5)};
	UPROPERTY(BlueprintReadWrite)
        TArray<FSlotStruct> Inventory;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	    bool PicksUpOrPickup = true;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	    int NumberOfInventorySlots = 15;
	UFUNCTION(BlueprintCallable)
	    void AddToInventory(TArray<FSlotStruct> content);
	UFUNCTION(BlueprintCallable)
	    void TestFunction();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};




/**do not use, does not work*/
//template <class ItemPropType>
//FORCEINLINE TSoftObjectPtr<ItemPropType> UInventoryComponent::GetItemAssetProperty(FString itemName, FString propertyName )
//{
//    //uint8 *a15 = TestTable.Get()->FindRowUnchecked(FName(itemName));
//	if(TestTable.IsValid())
//	{
//        if(const TArray<FName> a16 = TestTable->GetRowNames(); a16.Contains(FName(itemName)))
//	    {
//			const int a17 = a16.Find(FName(itemName));
//			if(propertyName != "")
//			{
//				if(TestTable.Get()->RowStruct->FindPropertyByName(FName(propertyName)))
//				{
//				    TArray<FString> a23 = DataTableUtils::GetColumnDataAsString(TestTable.Get(), FName(propertyName), EDataTableExportFlags::None);
//				    return TSoftObjectPtr<ItemPropType>(a23[a17]);
//				}
//			}
//            else
//            {
//                for(auto structPropertyName : DataTableUtils::GetStructPropertyNames(TestTable.Get()->RowStruct))
//			    {
//			        TArray<FString> columnData = DataTableUtils::GetColumnDataAsString(TestTable.Get(), structPropertyName, EDataTableExportFlags::None);
//				    if (TSoftObjectPtr<ItemPropType> a14 = TSoftObjectPtr<ItemPropType>(columnData[a17]); a14.IsValid())
//				    {
//				        return a14;
//				    }
//			    }
//            }
//	    }
//	}
//    return TSoftObjectPtr<ItemPropType>();
//}