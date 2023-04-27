// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class BACKROWSTUDIO_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
	virtual void NativeConstruct() override;
public:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UProgressBar* MyHealthBar;

	UPROPERTY()
	class AMainCharacter* MyPlayer;

	UFUNCTION()
	float GetHealth() const;
};