// Copyright Daniel Thompson https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

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

	// Set debug defaults
	GridSize = 7;
	TileSize = 100.f;
	Tiles.SetNum(GridSize * GridSize);

}

int32 ADropPointArenaController::getLinearIndex(const FDropPointGridCoord & coord) const
{
	return (coord.y * GridSize) + coord.x; 
}

int32 ADropPointArenaController::isInLinearRange(const int32 & linearIndex, const int32& size) const
{
	if (linearIndex >= 0 && linearIndex <= (((size -1) * size) + (size -1)))
	{
		return true;
	}
	return false;
}

void ADropPointArenaController::setTilePos(const FDropPointGridCoord & coord, ADropPointTileInteractive * tile)
{
	check(isInsideArena(coord));
	const int32 linearIndex = getLinearIndex(coord);
	check(isInLinearRange(linearIndex, GridSize));
	Tiles[linearIndex] = tile;
}

ADropPointTile* ADropPointArenaController::getTilePos(const FDropPointGridCoord & coord) const
{
	if (isInsideArena(coord))
	{
		const int32 linearIndex = getLinearIndex(coord);
		check(linearIndex >= 0 && linearIndex < Tiles.Num());
		return Tiles[linearIndex];
	}
	return nullptr;
}

ADropPointTile* ADropPointArenaController::getTileStep(const FDropPointGridCoord & origin, const FDropPointGridCoord & offset) const
{
	FDropPointGridCoord newCoords;
	newCoords.x = origin.x + offset.x;
	newCoords.y = origin.y + offset.y;
	return getTilePos(newCoords);
}

const bool ADropPointArenaController::isInsideArena(const FDropPointGridCoord & coord) const
{
	if (coord.x >= 0 && coord.x < GridSize)
	{
		if (coord.y >= 0 && coord.y < GridSize)
		{
			return true;
		}
	}
	return false;
}

void ADropPointArenaController::endTurn()
{
	//Launch Units
	//Unit Actions
	//Hazard Progression
	//Apply Damage
	TurnCount++;
}

void ADropPointArenaController::spawnArena()
{
	if (!TileTypeActor)
	{
		return;
	}
	// Calculate grid offset
	const int32 gridOffset = floor(((GridSize * TileSize) / 2) / 100) * 100;

	// Loop to spawn each block
	for (int32 blockXIndex = 0; blockXIndex < GridSize; blockXIndex++)
	{
		for (int32 blockYIndex = 0; blockYIndex < GridSize; blockYIndex++)
		{
			const float XOffset = (blockXIndex * TileSize) - gridOffset; // Divide by dimension
			const float YOffset = ((blockYIndex % GridSize) * TileSize) - gridOffset; // Modulo gives remainder

			// Make position vector, offset from Grid location
			const FVector blockLocation = FVector(XOffset, YOffset, 0.f) + GetActorLocation();

			// Spawn a block
			ADropPointTileInteractive* newTile = GetWorld()->SpawnActor<ADropPointTileInteractive>(TileTypeActor.GetDefaultObject()->GetClass(), blockLocation, FRotator(0, 0, 0));

			// Tell the block about its owner
			if (newTile != nullptr)
			{
				newTile->m_OwningGrid = this;

				FDropPointGridCoord tileCoord;
				tileCoord.x = (newTile->GetActorLocation().X + gridOffset) / TileSize;
				tileCoord.y = (newTile->GetActorLocation().Y + gridOffset) / TileSize;
				setTilePos(tileCoord, newTile);
			}
		}
	}
}

// Called when the game starts or when spawned
void ADropPointArenaController::BeginPlay()
{
	Super::BeginPlay();

	spawnArena();
}
