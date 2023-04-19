// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniMapComponent.h"

#include "MinimapWidget.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "GameFramework/GameSession.h"

// Sets default values for this component's properties
UMiniMapComponent::UMiniMapComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	//MySceneCaptureComponent2D.relative
}


//void UMiniMapComponent::ConstructMinimap(APlayerController* myPlayer, TSubclassOf<UUserWidget> inWidget, UMaterial* mat)
//{
//    UUserWidget *a = CreateWidget(myPlayer, inWidget->StaticClass());
//    UMinimapWidget *b = Cast<UMinimapWidget>(a);
//	if (b->IsValidLowLevel())
//	{
//	    b->MyMat = mat;
//		b->MyParent = this;
//	}
//
//	b->AddToViewport();
//}

// Called when the game starts
void UMiniMapComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UMiniMapComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{

}

