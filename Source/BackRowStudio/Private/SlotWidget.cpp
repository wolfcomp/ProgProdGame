// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotWidget.h"

// void USlotWidget::Synchronize()
//{
//     if(MyContent && MyContent.Item->IsValidLowLevel() && MyContent.Quantity != NULL)
//     {
//         if(MyContent)
//         {
//             if(MyContent.Item->MyImage)
//             {
//                 if(MyImage)
//                 {
//                     MyImage->BrushDelegate.BindUFunction(this, "SetImageField");
//                     MyImage->SynchronizeProperties();
//                 }
//             }
//             if (MyContent.Quantity && QuantityNum && QuantityTextBox)
//             {
//	            QuantityNum->TextDelegate.BindUFunction(this, "SetQuantityField");
//	            QuantityNum->SynchronizeProperties();
//             }
//         }
//         else
//         {
//             GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red,FString("a17 not valid"));
//         }
//     }
// }
//
// void USlotWidget::NativeConstruct()
//{
//     OrgImg = MyImage->Brush;
//     Synchronize();
// }
//
// bool USlotWidget::NativeOnDrop(const FGeometry &InGeometry, const FDragDropEvent &InDragDropEvent, UDragDropOperation *InOperation)
//{
//     if(const UInvDragDropOperation* inOperation2 = Cast<UInvDragDropOperation>(InOperation))
//     {
//         if(USlotWidget* inOp = Cast<USlotWidget>(inOperation2->WidgetReference); inOp)
//         {
//             if (inOp == this) return false;
//             if(inOp->MyContent)
//             {
//                 if(MyContent.Item == inOp->MyContent.Item)
//                 {
//                     MyContent.Quantity += inOp->MyContent.Quantity;
//                     GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Blue,FString("pog drop detected"));
//                     inOp->MyContent = FSlotStruct();
//                     Synchronize();
//                     return true;
//                 }
//                 if(!MyContent)
//                 {
//                     GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Yellow,FString("got nothin'"));
//                     MyContent = inOp->MyContent;
//                     inOp->MyContent = FSlotStruct();
//                     Synchronize();
//                     return true;
//                 }
//                 Synchronize();
//                 return false;
//             }
//             GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red,FString("invalid drop detected"));
//             return false;
//         }
//     }
//     GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red,FString("invalid drop detected"));
//     return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
// }
//
// void USlotWidget::NativeOnDragDetected(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent, UDragDropOperation *&OutOperation)
//{
//     //a lot taken from https://forums.unrealengine.com/t/creating-drag-and-drop-ui-using-c/269049
//     UInvDragDropOperation* itemDragDrop = NewObject<class UInvDragDropOperation>();
//     //this->SetVisibility(ESlateVisibility::HitTestInvisible);
//
//     itemDragDrop->WidgetReference = this;
//     itemDragDrop->DragOffset = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());
//     itemDragDrop->DefaultDragVisual = this;
//     itemDragDrop->Pivot = EDragPivot::MouseDown;
//     OutOperation = itemDragDrop;
//
//     Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
// }
//
// void USlotWidget::NativeOnDragCancelled(const FDragDropEvent &InDragDropEvent, UDragDropOperation *InOperation)
//{
//     GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Yellow,FString("drag cancelled"));
//     if(const UInvDragDropOperation* inOp = Cast<UInvDragDropOperation>(InOperation))
//     {
//         if(const USlotWidget* inOp2 = Cast<USlotWidget>(inOp->WidgetReference))
//         {
//             MyContent = inOp2->MyContent;
//         }
//     }
//     Super::NativeOnDragCancelled(InDragDropEvent, InOperation);
// }
//
// FReply USlotWidget::NativeOnMouseButtonDown(const FGeometry &InGeometry, const FPointerEvent &InMouseEvent)
//{
//     FReply returnReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
//     if(InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
//     {
//         //GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Black,FString("OnMouseButtonDown triggered with Mouse button"));
//         if(MyContent)
//         {
//             returnReply.DetectDrag(TakeWidget(),EKeys::LeftMouseButton);
//         }
//     }
//     else if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
//     {
//         GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Yellow,FString("OnMouseButtonDown triggered with right Mouse button"));
//         if(MyContent)
//         {
//             if(MyContent.Item->HasMenu)
//             {
//                 //if(myItem.HasMenu) CreateWidgetInstance();
//             }
//         }
//     }
//     return returnReply;
// }
//
// FText USlotWidget::SetQuantityField() const
//{
//     if(QuantityNum) return QuantityNum->GetText();
//     if(MyContent)
//     {
//         if(MyContent.Quantity >= 1) {
//             return FText::FromString(FString::FromInt(MyContent.Quantity));
//         }
//     }
//     return FText::FromString("");
// }
//
// FSlateBrush USlotWidget::SetImageField() const
//{
//     if(MyContent && MyContent.Item && MyContent.Item->MyImage)
//     {
//         return UWidgetBlueprintLibrary::MakeBrushFromTexture(MyContent.Item->MyImage.Get(), 32, 32);
//     }
//     //return MySlateBrush;
//     return FSlateBrush();
// }

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
