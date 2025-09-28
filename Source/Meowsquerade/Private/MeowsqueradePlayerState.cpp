// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/MeowsqueradePlayerState.h"

#include "EngineUtils.h"
#include "MeowsqueradeCharacter.h"
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
	DOREPLIFETIME(AMeowsqueradePlayerState, SkinIndex);
}

void AMeowsqueradePlayerState::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);

	if (AMeowsqueradePlayerState* PS = Cast<AMeowsqueradePlayerState>(PlayerState))
	{
		PS->SkinIndex = this->SkinIndex;
		PS->OnRep_SkinIndex();
	}
}

void AMeowsqueradePlayerState::OnRep_SkinIndex()
{
	if (AMeowsqueradeCharacter* Character = Cast<AMeowsqueradeCharacter>(GetAssociatedPawn()))
	{
		Character->SetSkeletonSkin(SkinIndex);
	}
}

APawn* AMeowsqueradePlayerState::GetAssociatedPawn() const
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return nullptr;
	}
 
	for (TActorIterator<APawn> It(World); It; ++It)
	{
		APawn* Pawn = *It;
		if (Pawn && Pawn->GetPlayerState() == this)
		{
			return Pawn;
		}
	}
 
	return nullptr;
}
