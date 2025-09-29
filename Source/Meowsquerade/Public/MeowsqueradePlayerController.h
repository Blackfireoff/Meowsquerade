// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MeowsqueradePlayerController.generated.h"

class UInputMappingContext;
class UUserWidget;

/**
 *  Simple first person Player Controller
 *  Manages the input mapping context.
 *  Overrides the Player Camera Manager class.
 */

UENUM(BlueprintType)
enum class EPlayerRole : uint8
{
	Mouse UMETA(DisplayName = "Mouse"),
	Cat UMETA(DisplayName = "Cat")
};

USTRUCT(BlueprintType)
struct FPlayerRoleInfo
{
	GENERATED_BODY()
 
	UPROPERTY()
	FString PlayerName;
 
	UPROPERTY()
	EPlayerRole Role;
};

UCLASS(abstract)
class MEOWSQUERADE_API AMeowsqueradePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	/** Constructor */
	AMeowsqueradePlayerController();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing=OnRep_PlayerRole, Category="Game")
	EPlayerRole PlayerRole;

	UFUNCTION(Client, Reliable)
	void Client_ReceiveRoleList(const TArray<FPlayerRoleInfo>& RoleList);
 
	// Local cached roles
	UPROPERTY(BlueprintReadOnly)
	TArray<FPlayerRoleInfo> CachedRoleList;

protected:

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category="Input|Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContexts;

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category="Input|Input Mappings")
	TArray<UInputMappingContext*> MobileExcludedMappingContexts;

	/** Mobile controls widget to spawn */
	UPROPERTY(EditAnywhere, Category="Input|Touch Controls")
	TSubclassOf<UUserWidget> MobileControlsWidgetClass;

	/** Pointer to the mobile controls widget */
	TObjectPtr<UUserWidget> MobileControlsWidget;

public:

	UFUNCTION(Server, Reliable)
	void ServerActivateTask(AActor* Target);

	UFUNCTION()
	void OnRep_PlayerRole();

protected:

	/** Gameplay initialization */
	virtual void BeginPlay() override;

	/** Input mapping context setup */
	virtual void SetupInputComponent() override;

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

};
