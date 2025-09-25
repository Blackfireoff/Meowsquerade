// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/MeowsqueradeGameState.h"
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
	UE_LOG(LogTemp, Warning, TEXT("Incrementing task count : %d"), TaskCount);
}

void AMeowsqueradeGameState::DecrementTaskCount()
{
	--TaskCount;
	UE_LOG(LogTemp, Warning, TEXT("Decrementing task count : %d"), TaskCount);

}
