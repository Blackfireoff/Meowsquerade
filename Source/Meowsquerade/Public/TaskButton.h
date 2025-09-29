// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MeowsqueradePlayerController.h"
#include "GameFramework/Actor.h"
#include "TaskButton.generated.h"

UCLASS()
class MEOWSQUERADE_API ATaskButton : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATaskButton();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ActivateTask(const EPlayerRole RoleState);
};
