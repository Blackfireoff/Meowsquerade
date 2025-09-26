// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"

#include "GameFramework/GameStateBase.h"

ALobbyGameMode::ALobbyGameMode()
{
	bUseSeamlessTravel = true;
}

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (GameState.Get()->PlayerArray.Num() == MinPlayerCount)
	{
		GetWorld()->ServerTravel("/Game/Maps/Lvl_FirstPerson?listen");
	}
}
