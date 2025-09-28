// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MEOWSQUERADE_API ALobbyGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	ALobbyGameMode();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LobbyGameMode")
	int32 MinPlayerCount = 2;
	
	virtual void PostLogin(APlayerController* NewPlayer) override;

	FTimerHandle TimerHandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LobbyGameMode")
	float StartGameDelay = 2.f;
};
