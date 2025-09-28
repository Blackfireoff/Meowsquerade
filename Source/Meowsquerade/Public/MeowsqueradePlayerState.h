// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MeowsqueradePlayerState.generated.h"

UENUM(BlueprintType)
enum class ERoleState : uint8
{
	Mouse    UMETA(DisplayName = "Mouse"),
	Cat UMETA(DisplayName = "Cat")
};

/**
 * 
 */
UCLASS()
class MEOWSQUERADE_API AMeowsqueradePlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated, Category="Game")
	ERoleState RoleState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing=OnRep_SkinIndex, Category="Game")
	int32 SkinIndex = 0;

	AMeowsqueradePlayerState();

	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void CopyProperties(APlayerState* PlayerState) override;

	UFUNCTION()
	void OnRep_SkinIndex();

	UFUNCTION()
	APawn* GetAssociatedPawn() const;
	
};
