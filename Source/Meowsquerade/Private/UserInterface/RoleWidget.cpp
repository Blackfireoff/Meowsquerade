// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/RoleWidget.h"
#include "Components/TextBlock.h"

void URoleWidget::RefreshRole(EPlayerRole Role)
{
	TxtRole->SetText(FText::FromString(FString::Printf(TEXT("My role : %s"), *PlayerRoleUtils::ToString(Role))));
	TxtRole->SetColorAndOpacity(Role == EPlayerRole::Mouse ? FSlateColor(FLinearColor::Blue) : FSlateColor(FLinearColor::Red));
}

void URoleWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (AMeowsqueradePlayerController* PC = Cast<AMeowsqueradePlayerController>(GetOwningPlayer()))
	{
		PC->OnRoleChanged.AddDynamic(this, &URoleWidget::RefreshRole);
		RefreshRole(PC->PlayerRole);
	}
}

void URoleWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if (AMeowsqueradePlayerController* PC = Cast<AMeowsqueradePlayerController>(GetOwningPlayer()))
	{
		PC->OnRoleChanged.RemoveDynamic(this, &URoleWidget::RefreshRole);
	}
}
