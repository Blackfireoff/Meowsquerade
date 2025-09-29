// Copyright Epic Games, Inc. All Rights Reserved.


#include "Public/MeowsqueradePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "Public/MeowsqueradeCameraManager.h"
#include "Blueprint/UserWidget.h"
#include "Meowsquerade.h"
#include "TaskButton.h"
#include "Net/UnrealNetwork.h"
#include "Widgets/Input/SVirtualJoystick.h"

AMeowsqueradePlayerController::AMeowsqueradePlayerController()
{
	// set the player camera manager class
	PlayerCameraManagerClass = AMeowsqueradeCameraManager::StaticClass();

	bReplicates = true;
}

void AMeowsqueradePlayerController::Client_ReceiveRoleList_Implementation(const TArray<FPlayerRoleInfo>& RoleList)
{
	CachedRoleList = RoleList;
	UE_LOG(LogTemp, Log, TEXT("Received %d player roles"), CachedRoleList.Num());
	for (const FPlayerRoleInfo& RoleInfo : CachedRoleList)
	{
		UE_LOG(LogTemp, Log, TEXT("Player: %s, Role: %s"), *RoleInfo.PlayerName, *UEnum::GetValueAsString(RoleInfo.Role));
		GEngine->AddOnScreenDebugMessage(
				-1,
				10.f,
				RoleInfo.Role == EPlayerRole::Mouse ? FColor::Blue : FColor::Red,
				FString::Printf(TEXT("Le joueur '%s' a pour rôle %s"), *RoleInfo.PlayerName, RoleInfo.Role == EPlayerRole::Mouse ? TEXT("MOUSE") : TEXT("CAT")));
	}
}

void AMeowsqueradePlayerController::ServerActivateTask_Implementation(AActor* Target)
{
	if (!HasAuthority()) return;
	if (ATaskButton* TaskButton = Cast<ATaskButton>(Target))
	{
			TaskButton->ActivateTask(PlayerRole);
	}
}

void AMeowsqueradePlayerController::OnRep_PlayerRole()
{
	GEngine->AddOnScreenDebugMessage(
				-1,
				10.f,
				PlayerRole == EPlayerRole::Mouse ? FColor::Blue : FColor::Red,
				FString::Printf(TEXT("Mon rôle est : %s"), PlayerRole == EPlayerRole::Mouse ? TEXT("MOUSE") : TEXT("CAT")));
}

void AMeowsqueradePlayerController::BeginPlay()
{
	Super::BeginPlay();

	
	// only spawn touch controls on local player controllers
	if (SVirtualJoystick::ShouldDisplayTouchInterface() && IsLocalPlayerController())
	{
		// spawn the mobile controls widget
		MobileControlsWidget = CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);

		if (MobileControlsWidget)
		{
			// add the controls to the player screen
			MobileControlsWidget->AddToPlayerScreen(0);

		} else {

			UE_LOG(LogMeowsquerade, Error, TEXT("Could not spawn mobile controls widget."));

		}

	}
}

void AMeowsqueradePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Context
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}

			// only add these IMCs if we're not using mobile touch input
			if (!SVirtualJoystick::ShouldDisplayTouchInterface())
			{
				for (UInputMappingContext* CurrentContext : MobileExcludedMappingContexts)
				{
					Subsystem->AddMappingContext(CurrentContext, 0);
				}
			}
		}
	}
	
}

void AMeowsqueradePlayerController::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMeowsqueradePlayerController, PlayerRole);
}
