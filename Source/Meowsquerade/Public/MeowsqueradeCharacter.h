// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MeowsqueradePlayerState.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "MeowsqueradeCharacter.generated.h"

class ASkinButton;
class ATaskButton;
class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *  A basic first person character
 */
UCLASS(abstract)
class AMeowsqueradeCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: first person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* FirstPersonMesh;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

protected:

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category ="Input")
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category ="Input")
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, Category ="Input")
	class UInputAction* LookAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, Category ="Input")
	class UInputAction* MouseLookAction;
	
	UPROPERTY(EditAnywhere, Category ="Input")
	UInputAction* InteractAction;
	
public:
	AMeowsqueradeCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Skin")
	UDataAsset* CharacterSkin;

protected:

	/** Called from Input Actions for movement input */
	void MoveInput(const FInputActionValue& Value);

	/** Called from Input Actions for looking input */
	void LookInput(const FInputActionValue& Value);

	/** Handles aim inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoAim(float Yaw, float Pitch);

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles jump start inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();

	/** Handles jump end inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();

	void InteractInput();

	/** Set up input action bindings */
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	

public:

	/** Returns the first person mesh **/
	USkeletalMeshComponent* GetFirstPersonMesh() const { return FirstPersonMesh; }

	/** Returns first person camera component **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	void SetSkeletonSkin(int32 SkinIndex);

	UFUNCTION(Server, Reliable)
	void ServerSetSkinIndex(int32 NewIndex);

	virtual void BeginPlay() override;

private :
	void InteractWithTaskButton(ATaskButton* HitTaskButton);

	void InteractWithSkinButton(ASkinButton* HitSkinButton);

};

inline void AMeowsqueradeCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (AMeowsqueradePlayerState* PS = Cast<AMeowsqueradePlayerState>(GetPlayerState()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Constructor Skin Index: %d"), PS->SkinIndex);
		SetSkeletonSkin(PS->SkinIndex);
	}
}

