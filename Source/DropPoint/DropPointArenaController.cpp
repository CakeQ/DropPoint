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

void ADropPointArenaController::setTilePos(const FDropPointGridCoord & coord, ADropPointTileInteractive * tile)
{
	check(isInsideArena(coord));
	const int32 linearIndex = getLinearIndex(coord);
	check(linearIndex >= 0 && linearIndex < m_Tiles.Num());
	m_Tiles[linearIndex] = tile;
}

ADropPointTileInteractive* ADropPointArenaController::getTilePos(const FDropPointGridCoord & coord, bool & outOfBounds) const
{
	outOfBounds = true;
	if (isInsideArena(coord))
	{
		const int32 linearIndex = getLinearIndex(coord);
		check(linearIndex >= 0 && linearIndex < m_Tiles.Num());
		outOfBounds = false;
		return m_Tiles[linearIndex];
	}
	return nullptr;
}

const bool ADropPointArenaController::isInsideArena(const FDropPointGridCoord & coord) const
{
	if (coord.x >= 0 && coord.x < m_GridSize)
	{
		if (coord.y >= 0 && coord.y < m_GridSize)
		{
			return true;
		}
	}
	return false;
}

// Called when the game starts or when spawned
void ADropPointArenaController::BeginPlay()
{
	Super::BeginPlay();

	// Calculate grid offset
	const int32 gridOffset = floor(((m_GridSize * m_BlockSpacing) / 2) / 100) * 100;

	// Loop to spawn each block
	for (int32 blockXIndex = 0; blockXIndex < m_GridSize; blockXIndex++)
	{
		for (int32 blockYIndex = 0; blockYIndex < m_GridSize; blockYIndex++)
		{
			const float XOffset = ((blockXIndex / m_GridSize) * m_BlockSpacing) - gridOffset; // Divide by dimension
			const float YOffset = ((blockYIndex%m_GridSize) * m_BlockSpacing) - gridOffset; // Modulo gives remainder

			// Make position vector, offset from Grid location
			const FVector blockLocation = FVector(XOffset, YOffset, 0.f) + GetActorLocation();

			// Spawn a block
			ADropPointTileInteractive* newTile = GetWorld()->SpawnActor<ADropPointTileInteractive>(blockLocation, FRotator(0, 0, 0));

			// Tell the block about its owner
			if (newTile != nullptr)
			{
				newTile->m_OwningGrid = this;

				FDropPointGridCoord tileCoord;
				tileCoord.x = newTile->GetActorLocation().X;
				tileCoord.y = newTile->GetActorLocation().Y;
				setTilePos(tileCoord, newTile);
			}
		}
	}
}
