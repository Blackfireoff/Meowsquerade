// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MeowsqueradePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class MEOWSQUERADE_API AMeowsqueradePlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing=OnRep_SkinIndex, Category="Game")
	int32 SkinIndex = 0;

	AMeowsqueradePlayerState();

	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void CopyProperties(APlayerState* PlayerState) override;

	UFUNCTION()
	void OnRep_SkinIndex();
};
