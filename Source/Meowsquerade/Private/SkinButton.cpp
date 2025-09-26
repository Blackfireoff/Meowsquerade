// Fill out your copyright notice in the Description page of Project Settings.


#include "SkinButton.h"


// Sets default values
ASkinButton::ASkinButton()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;
}

// Called when the game starts or when spawned
void ASkinButton::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkinButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

