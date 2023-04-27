// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthBarWidget.h"
#include "MainCharacter.h"
#include "Components/ProgressBar.h"

void UHealthBarWidget::NativeConstruct()
{
    Super::NativeConstruct();
    MyHealthBar->PercentDelegate.BindUFunction(this,"GetHealth");
    MyHealthBar->SynchronizeProperties();
}

float UHealthBarWidget::GetHealth() const
{
    return MyPlayer->Health / MyPlayer->MaxHealth;
}