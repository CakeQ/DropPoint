// Copyright Daniel Thompson https://www.cakedan.net/ and Archie Whitehead 2019 All Rights Reserved.

#include "DropPointArenaController.h"
#include "Tiles/DropPointTile.h"
#include "Tiles/DropPointTileInteractive.h"
#include "Components/TextRenderComponent.h"
#include "Engine/World.h"

// Sets default values
ADropPointArenaController::ADropPointArenaController()
{
	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Set defaults
	m_GridSize = 7;
	m_BlockSpacing = 100.f;

}

// Called when the game starts or when spawned
void ADropPointArenaController::BeginPlay()
{
	Super::BeginPlay();
	
	// Number of blocks
	const int32 NumBlocks = m_GridSize * m_GridSize;

	// Calculate grid offset

	const int32 gridOffset = floor(((m_GridSize * m_BlockSpacing) / 2) / 100) * 100;

	// Loop to spawn each block
	for (int32 blockIndex = 0; blockIndex < NumBlocks; blockIndex++)
	{
		const float XOffset = ((blockIndex / m_GridSize) * m_BlockSpacing) - gridOffset; // Divide by dimension
		const float YOffset = ((blockIndex%m_GridSize) * m_BlockSpacing) - gridOffset; // Modulo gives remainder

		// Make position vector, offset from Grid location
		const FVector blockLocation = FVector(XOffset, YOffset, 0.f) + GetActorLocation();

		// Spawn a block
		ADropPointTileInteractive* newTile = GetWorld()->SpawnActor<ADropPointTileInteractive>(blockLocation, FRotator(0, 0, 0));

		// Tell the block about its owner
		if (newTile != nullptr)
		{
			newTile->m_OwningGrid = this;
		}
	}

}
