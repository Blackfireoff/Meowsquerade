// Copyright Epic Games, Inc. All Rights Reserved.

#include "Public/MeowsqueradeGameMode.h"

#include "MeowsqueradePlayerState.h"

AMeowsqueradeGameMode::AMeowsqueradeGameMode()
{
	
}

void AMeowsqueradeGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (NewPlayer && NewPlayer->PlayerState)
	{
		AMeowsqueradePlayerState* MeowsqueradePlayerState = Cast<AMeowsqueradePlayerState>(NewPlayer->PlayerState);
		if (MeowsqueradePlayerState)
		{
			MeowsqueradePlayerState->RoleState = bIsFirstPlayerMouse ? ERoleState::Mouse : ERoleState::Cat;
			GEngine->AddOnScreenDebugMessage(
				-1,
				5.f,
				bIsFirstPlayerMouse ? FColor::Blue : FColor::Red,
				FString::Printf(TEXT("[%d] Mon rôle : %s"), MeowsqueradePlayerState->GetPlayerId(), bIsFirstPlayerMouse ? TEXT("MOUSE") : TEXT("CAT")));
			bIsFirstPlayerMouse = !bIsFirstPlayerMouse;
			
		}
	}
}
