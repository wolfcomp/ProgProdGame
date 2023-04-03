// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotWidget.h"

#include "InvDragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void USlotWidget::NativeConstruct()
{
    MyCon = &MyContent;
    if(MyCon)
    {
        if (MyCon->MyItem.MyImage && MyImage)
        {
            MyImage->BrushDelegate.BindUFunction(this, "SetImageField");
            MyImage->SynchronizeProperties();
        }
        if (MyCon->Quantity && QuantityNum && QuantityTextBox)
        {
	        QuantityNum->TextDelegate.BindUFunction(this, "SetQuantityField");
	        QuantityNum->SynchronizeProperties();
        }
    }
}

bool USlotWidget::NativeOnDrop(const FGeometry &InGeometry, const FDragDropEvent &InDragDropEvent, UDragDropOperation *InOperation)
{
    UInvDragDropOperation* InOp = Cast<UInvDragDropOperation>(InOperation);

    if(InOp)
    {
        GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Green,FString("valid drop detected"));
        if(MyCon == nullptr)
        {
            MyCon = &InOp->MyContent;
            return true;
        } if(&MyCon->MyItem == &InOp->MyContent.MyItem)
        {
            return true;
        }
        return true;
    }
    GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red,FString("invalid drop detected"));
    return false;
    //return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

void USlotWidget::NativeOnDragDetected(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent, UDragDropOperation *&OutOperation)
{
    UInvDragDropOperation* ItemDragDrop = NewObject<UInvDragDropOperation>();
    if (ItemDragDrop != nullptr)
    {
        GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Green,FString("valid drag detected"));
        OldContent = MyCon;
        if (MyCon == nullptr)
        {
            ItemDragDrop->MyContent = FSlotStruct();
        } else
        {
            ItemDragDrop->MyContent = *MyCon;
            MyCon = nullptr;
        }
        OutOperation = ItemDragDrop;
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red,FString("invalid drag detected"));
    }

    Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
}

void USlotWidget::NativeOnDragCancelled(const FDragDropEvent &InDragDropEvent, UDragDropOperation *InOperation)
{
    GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Yellow,FString("drag cancelled"));
    MyCon = OldContent;
    Super::NativeOnDragCancelled(InDragDropEvent, InOperation);
}

FReply USlotWidget::NativeOnMouseButtonDown(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent)
{
    FReply returnReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
    if(InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
    {
        //GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Black,FString("OnMouseButtonDown triggered with Mouse button"));
        returnReply.DetectDrag(TakeWidget(),EKeys::LeftMouseButton);
    }
    else
    {
         //GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Black,FString("OnMouseButtonDown triggered with non Mouse button"));
    }

    return returnReply;
}


FText USlotWidget::SetQuantityField() const
{
    if(MyCon != nullptr)
    {
        if(MyCon->Quantity != 0) {
        QuantityTextBox->SetVisibility(ESlateVisibility::Visible);
        return FText::FromString(FString::FromInt(MyCon->Quantity));
        }
    }
    return FText::FromString("");
}

FSlateBrush USlotWidget::SetImageField() const
{
    if(MyCon != nullptr)
    {
        return UWidgetBlueprintLibrary::MakeBrushFromTexture(MyCon->MyItem.MyImage, 32, 32);
    }

    return FSlateBrush();
}

