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

	void TravelToLobby();

	virtual void HandleSeamlessTravelPlayer(AController*& C) override;

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game")
	bool bIsFirstPlayerMouse = true;

	void SendRoleListToMeanPlayers();
	
};



