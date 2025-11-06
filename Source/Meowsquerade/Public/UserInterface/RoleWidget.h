// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MeowsqueradeGameState.h"
#include "MeowsqueradePlayerController.h"
#include "Blueprint/UserWidget.h"
#include "RoleWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class MEOWSQUERADE_API URoleWidget : public UUserWidget
{
	GENERATED_BODY()

public :
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TxtRole = nullptr;

	UFUNCTION(BlueprintCallable)
	void RefreshRole(EPlayerRole Role);

protected :
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;
};
