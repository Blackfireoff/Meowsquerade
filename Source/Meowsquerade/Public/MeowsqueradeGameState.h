// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MeowsqueradeGameState.generated.h"

/**
 * 
 */
UCLASS()
class MEOWSQUERADE_API AMeowsqueradeGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category="Game")
	int32 TaskCount = 3;

	AMeowsqueradeGameState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Category="Game")
	void IncrementTaskCount();

	UFUNCTION(BlueprintCallable, Category="Game")
	void DecrementTaskCount();
	
};
