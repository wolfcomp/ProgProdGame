// Fill out your copyright notice in the Description page of Project Settings.


#include "DragPreview.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"

FSlateBrush UDragPreview::SetImageField() const
{
    if(MyImage && Image)
    {
        return UWidgetBlueprintLibrary::MakeBrushFromTexture(Content.Item->MyImage.Get(), 32, 32);
    }
    return FSlateBrush();
}

void UDragPreview::NativeTick(const FGeometry &MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
}

void UDragPreview::NativeConstruct()
{
    //if(MyImage)
    //{
    //    MyImage->BrushDelegate.BindUFunction(this, "SetImageField");
    //    MyImage->SynchronizeProperties();
    //}
    Super::NativeConstruct();
}
