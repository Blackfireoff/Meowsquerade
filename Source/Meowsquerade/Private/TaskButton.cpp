// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskButton.h"

#include "MeowsqueradeGameState.h"


// Sets default values
ATaskButton::ATaskButton()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// set the static mesh
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

}

// Called when the game starts or when spawned
void ATaskButton::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATaskButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATaskButton::ActivateTask(const ERoleState RoleState)
{
	AMeowsqueradeGameState* GS = GetWorld()->GetGameState<AMeowsqueradeGameState>();
	if (GS)
	{
		switch (RoleState)
		{
		case ERoleState::Cat:
			GS->DecrementTaskCount();
			break;
		case ERoleState::Mouse:
			GS->IncrementTaskCount();
			break;
		default:
			UE_LOG(LogTemp, Error, TEXT("An unknown role tried to activate a task button!"));
			break;
		}
	}
}

