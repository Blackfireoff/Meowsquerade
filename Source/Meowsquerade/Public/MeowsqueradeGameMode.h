// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MeowsqueradeGameMode.generated.h"

/**
 *  Simple GameMode for a first person game
 */
UCLASS(abstract)
class AMeowsqueradeGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	AMeowsqueradeGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game", meta=(AllowPrivateAccess="true"))
	bool bIsFirstPlayerMouse = true; 
};



