// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/MeowsqueradePlayerState.h"
#include "Net/UnrealNetwork.h"

AMeowsqueradePlayerState::AMeowsqueradePlayerState()
{
	bReplicates = true;
}

void AMeowsqueradePlayerState::BeginPlay()
{
	Super::BeginPlay();

}

void AMeowsqueradePlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMeowsqueradePlayerState, RoleState);
}
