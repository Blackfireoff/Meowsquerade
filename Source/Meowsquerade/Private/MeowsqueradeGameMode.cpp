// Copyright Epic Games, Inc. All Rights Reserved.

#include "Public/MeowsqueradeGameMode.h"

#include "MeowsqueradePlayerController.h"
#include "MeowsqueradePlayerState.h"
#include "GameFramework/GameStateBase.h"

AMeowsqueradeGameMode::AMeowsqueradeGameMode()
{
	bUseSeamlessTravel = true;
}

void AMeowsqueradeGameMode::PostLogin(APlayerController* NewPlayer)
{
	UE_LOG(LogTemp, Warning, TEXT("POSTLOGIN"));

	Super::PostLogin(NewPlayer);
}

void AMeowsqueradeGameMode::TravelToLobby()
{
	GetWorld()->ServerTravel("Game/Maps/Lvl_Lobby?listen", true);
}

void AMeowsqueradeGameMode::HandleSeamlessTravelPlayer(AController*& C)
{
	UE_LOG(LogTemp, Warning, TEXT("HandleSeamlessTravelPlayer on dest GM for %s"), *GetNameSafe(C));
	Super::HandleSeamlessTravelPlayer(C);


	if (C)
	{
		if (AMeowsqueradePlayerController* PC = Cast<AMeowsqueradePlayerController>(C))
		{
			PC->PlayerRole = bIsFirstPlayerMouse ? EPlayerRole::Mouse : EPlayerRole::Cat;
			bIsFirstPlayerMouse = !bIsFirstPlayerMouse;
			PC->OnRep_PlayerRole();
		}

		SendRoleListToMeanPlayers();
	}
	
}

void AMeowsqueradeGameMode::SendRoleListToMeanPlayers()
{
	if (!GameState || !HasAuthority()) return;
	
	TArray<FPlayerRoleInfo> RoleList;
	for (APlayerState* PS : GameState->PlayerArray)
	{
		if (AMeowsqueradePlayerState* MeowsqueradePlayerState = Cast<AMeowsqueradePlayerState>(PS))
		{
			if (AMeowsqueradePlayerController* MeowsqueradePlayerController = Cast<AMeowsqueradePlayerController>(PS->GetPlayerController()))
			{
				FPlayerRoleInfo Info;
				Info.PlayerName = MeowsqueradePlayerState->GetPlayerName();
				Info.Role = MeowsqueradePlayerController->PlayerRole;
				RoleList.Add(Info);
			}
		}
	}

	for (APlayerState* PS : GameState->PlayerArray)
	{
		if (AMeowsqueradePlayerController* MeowsqueradePlayerController = Cast<AMeowsqueradePlayerController>(PS->GetPlayerController()))
		{
			if (MeowsqueradePlayerController->PlayerRole == EPlayerRole::Cat)
			{
				MeowsqueradePlayerController->Client_ReceiveRoleList(RoleList);
			}
		}
	}
}
