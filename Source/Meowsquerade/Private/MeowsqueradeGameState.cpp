// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/MeowsqueradeGameState.h"

#include "MeowsqueradeGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

AMeowsqueradeGameState::AMeowsqueradeGameState()
{
	bReplicates = true;
}

void AMeowsqueradeGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMeowsqueradeGameState, TaskCount);
}

void AMeowsqueradeGameState::IncrementTaskCount()
{
	++TaskCount;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Incrementing task count : %d"), TaskCount));
	UE_LOG(LogTemp, Warning, TEXT("Incrementing task count : %d"), TaskCount);
}

void AMeowsqueradeGameState::DecrementTaskCount()
{
	--TaskCount;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Decrementing task count : %d"), TaskCount));
	UE_LOG(LogTemp, Warning, TEXT("Decrementing task count : %d"), TaskCount);

	if (TaskCount == 0)
	{
		MouseWinGame();
	}
}

void AMeowsqueradeGameState::MouseWinGame()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Les MOUSE ont gagné !"));
	if (AMeowsqueradeGameMode* MeowsqueradeGameMode = Cast<AMeowsqueradeGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		MeowsqueradeGameMode->TravelToLobby();
	}
}
