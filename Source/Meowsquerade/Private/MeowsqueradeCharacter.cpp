// Copyright Epic Games, Inc. All Rights Reserved.

#include "Public/MeowsqueradeCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Meowsquerade.h"
#include "MeowsqueradePlayerController.h"
#include "SkinButton.h"
#include "SkinDataAsset.h"
#include "TaskButton.h"

AMeowsqueradeCharacter::AMeowsqueradeCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	
	// Create the first person mesh that will be viewed only by this character's owner
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("First Person Mesh"));

	FirstPersonMesh->SetupAttachment(GetMesh());
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
	FirstPersonMesh->SetCollisionProfileName(FName("NoCollision"));

	// Create the Camera Component	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCameraComponent->SetupAttachment(FirstPersonMesh, FName("head"));
	FirstPersonCameraComponent->SetRelativeLocationAndRotation(FVector(-2.8f, 5.89f, 0.0f), FRotator(0.0f, 90.0f, -90.0f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	FirstPersonCameraComponent->bEnableFirstPersonFieldOfView = true;
	FirstPersonCameraComponent->bEnableFirstPersonScale = true;
	FirstPersonCameraComponent->FirstPersonFieldOfView = 70.0f;
	FirstPersonCameraComponent->FirstPersonScale = 0.6f;

	// configure the character comps
	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::WorldSpaceRepresentation;

	GetCapsuleComponent()->SetCapsuleSize(34.0f, 96.0f);

	// Configure character movement
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	GetCharacterMovement()->AirControl = 0.5f;
	
	bReplicates = true;
}

void AMeowsqueradeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AMeowsqueradeCharacter::DoJumpStart);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMeowsqueradeCharacter::DoJumpEnd);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMeowsqueradeCharacter::MoveInput);

		// Looking/Aiming
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMeowsqueradeCharacter::LookInput);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AMeowsqueradeCharacter::LookInput);

		// Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AMeowsqueradeCharacter::InteractInput);
	}
	else
	{
		UE_LOG(LogMeowsquerade, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AMeowsqueradeCharacter::SetSkeletonSkin(int32 SkinIndex)
{
	if (USkinDataAsset* SkinDataAsset = Cast<USkinDataAsset>(CharacterSkin))
	{
		if (USkeletalMesh* NewMesh = Cast<USkeletalMesh>(SkinDataAsset->GetSkinMeshByIndex(SkinIndex)))
		{
			GetMesh()->SetSkeletalMesh(NewMesh);
			FirstPersonMesh->SetSkeletalMesh(NewMesh);
			if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
			{
				AnimInstance->InitializeAnimation();
			}
			if (UAnimInstance* FPAnimInstance = FirstPersonMesh->GetAnimInstance())
			{
				FPAnimInstance->InitializeAnimation();
			}
		}
		else
		{
			UE_LOG(LogMeowsquerade, Error, TEXT("'%s' Failed to find a Skeletal Mesh in the CharacterSkin Data Asset with the name '%d'."), *GetNameSafe(this), SkinIndex);
		}
	}
}

void AMeowsqueradeCharacter::InteractWithTaskButton(ATaskButton* HitTaskButton)
{
	if (AMeowsqueradePlayerController* PC = Cast<AMeowsqueradePlayerController>(GetController()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Task Button: %s"), *HitTaskButton->GetName());
		PC->ServerActivateTask(HitTaskButton);
	}
}

void AMeowsqueradeCharacter::InteractWithSkinButton(ASkinButton* HitSkinButton)
{
	ServerSetSkinIndex(HitSkinButton->SkinIndex);
}


void AMeowsqueradeCharacter::MoveInput(const FInputActionValue& Value)
{
	// get the Vector2D move axis
	FVector2D MovementVector = Value.Get<FVector2D>();

	// pass the axis values to the move input
	DoMove(MovementVector.X, MovementVector.Y);

}

void AMeowsqueradeCharacter::LookInput(const FInputActionValue& Value)
{
	// get the Vector2D look axis
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// pass the axis values to the aim input
	DoAim(LookAxisVector.X, LookAxisVector.Y);

}

void AMeowsqueradeCharacter::DoAim(float Yaw, float Pitch)
{
	if (GetController())
	{
		// pass the rotation inputs
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void AMeowsqueradeCharacter::DoMove(float Right, float Forward)
{
	if (GetController())
	{
		// pass the move inputs
		AddMovementInput(GetActorRightVector(), Right);
		AddMovementInput(GetActorForwardVector(), Forward);
	}
}

void AMeowsqueradeCharacter::DoJumpStart()
{
	// pass Jump to the character
	Jump();
}

void AMeowsqueradeCharacter::DoJumpEnd()
{
	// pass StopJumping to the character
	StopJumping();
}

void AMeowsqueradeCharacter::InteractInput()
{
	FVector Start;
	FRotator Rotation;
	GetController()->GetPlayerViewPoint(Start, Rotation);

	FVector End = Start + (Rotation.Vector() * 300.f);

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	//UE_LOG(LogTemp, Warning, TEXT("Line Trace Start: %s, End: %s"), *Start.ToString(), *End.ToString());
	
	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
	{
		if (ATaskButton* HitTaskButton = Cast<ATaskButton>(Hit.GetActor()))
		{
			InteractWithTaskButton(HitTaskButton);
		} else if (ASkinButton* HitSkinButton = Cast<ASkinButton>(Hit.GetActor()))
		{
			InteractWithSkinButton(HitSkinButton);
		}
	}
}

void AMeowsqueradeCharacter::ServerSetSkinIndex_Implementation(int32 NewIndex)
{
	if (!HasAuthority()) return;
	if (AMeowsqueradePlayerState* PS = Cast<AMeowsqueradePlayerState>(GetPlayerState()))
	{
		if (PS->SkinIndex == NewIndex) return;
				
		PS->SkinIndex = NewIndex;
		SetSkeletonSkin(NewIndex);
	}
}

void AMeowsqueradeCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	

	
}

void AMeowsqueradeCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	UE_LOG(LogTemp, Warning, TEXT("PossessedBy %s  HasAuthority=%d  LocalRole=%d  RemoteRole=%d"),
	   *GetName(), HasAuthority() ? 1 : 0, (int32)GetLocalRole(), (int32)GetRemoteRole());
	if (AMeowsqueradePlayerState* PS = Cast<AMeowsqueradePlayerState>(GetPlayerState()))
	{
		UE_LOG(LogTemp, Warning, TEXT("PossessedBy called, setting skin to index: %d, %s"), PS->SkinIndex, *GetName());
		GEngine->AddOnScreenDebugMessage(-1, 1000.f, FColor::Yellow, FString::Printf(TEXT("BeginPlay called, setting skin to index: %d, %s"), PS->SkinIndex, *GetName()));
		SetSkeletonSkin(PS->SkinIndex);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("BeginPlay called, but no PlayerState found: %s"), *GetName());
		GEngine->AddOnScreenDebugMessage(-1, 1000.f, FColor::Red, FString::Printf(TEXT("BeginPlay called, but no PlayerState found: %s"), *GetName()));
	}
	
}

void AMeowsqueradeCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (AMeowsqueradePlayerState* PS = Cast<AMeowsqueradePlayerState>(GetPlayerState()))
	{
		UE_LOG(LogTemp, Warning, TEXT("OnRep_PlayerState called, setting skin to index: %d, %s"), PS->SkinIndex, *GetName());
		GEngine->AddOnScreenDebugMessage(-1, 1000.f, FColor::Yellow, FString::Printf(TEXT("BeginPlay called, setting skin to index: %d, %s"), PS->SkinIndex, *GetName()));
		SetSkeletonSkin(PS->SkinIndex);
	}
}