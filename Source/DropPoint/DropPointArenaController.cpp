// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#include "DropPointArenaController.h"


// Sets default values
ADropPointArenaController::ADropPointArenaController()
{
	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;
}

// Called when the game starts or when spawned
void ADropPointArenaController::BeginPlay()
{
	Super::BeginPlay();
}
