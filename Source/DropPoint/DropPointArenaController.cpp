// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#include "DropPointArenaController.h"
#include "Tiles/DropPointTile.h"
#include "Tiles/DropPointTileInteractive.h"
#include "Engine/World.h"

// Sets default values
ADropPointArenaController::ADropPointArenaController()
{
	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;
}

int32 ADropPointArenaController::GetLinearIndex(const FDropPointGridCoord & coord) const
{
	return (coord.y * GridSize) + coord.x; 
}

int32 ADropPointArenaController::IsInLinearRange(const int32 & linearIndex, const int32& size) const
{
	if (linearIndex >= 0 && linearIndex <= (((size -1) * size) + (size -1)))
	{
		return true;
	}
	return false;
}

void ADropPointArenaController::SetTilePos(const FDropPointGridCoord & coord, ADropPointTileInteractive * tile)
{
	check(IsInsideArena(coord));
	const int32 linearIndex = GetLinearIndex(coord);
	check(IsInLinearRange(linearIndex, GridSize));
	Tiles[linearIndex] = tile;
}

ADropPointTile* ADropPointArenaController::GetTilePos(const FDropPointGridCoord & coord) const
{
	if (IsInsideArena(coord))
	{
		const int32 linearIndex = GetLinearIndex(coord);
		check(linearIndex >= 0 && linearIndex < Tiles.Num());
		return Tiles[linearIndex];
	}
	return nullptr;
}

ADropPointTile* ADropPointArenaController::GetTileStep(const FDropPointGridCoord & origin, const FDropPointGridCoord & offset) const
{
	FDropPointGridCoord newCoords;
	newCoords.x = origin.x + offset.x;
	newCoords.y = origin.y + offset.y;
	return GetTilePos(newCoords);
}

const bool ADropPointArenaController::IsInsideArena(const FDropPointGridCoord & coord) const
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

void ADropPointArenaController::EndTurn()
{
	//Launch Units
	//Unit Actions
	//Hazard Progression
	//Apply Damage
}

void ADropPointArenaController::SpawnArena()
{
	if (!TileTypeClass)
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
			ADropPointTileInteractive* newTile = GetWorld()->SpawnActor<ADropPointTileInteractive>(TileTypeClass.GetDefaultObject()->GetClass(), blockLocation, FRotator(0, 0, 0));

			// Tell the block about its owner
			if (newTile != nullptr)
			{
				newTile->OwningGrid = this;

				FDropPointGridCoord tileCoord;
				tileCoord.x = (newTile->GetActorLocation().X + gridOffset) / TileSize;
				tileCoord.y = (newTile->GetActorLocation().Y + gridOffset) / TileSize;
				SetTilePos(tileCoord, newTile);
			}
		}
	}
}

// Called when the game starts or when spawned
void ADropPointArenaController::BeginPlay()
{
	Super::BeginPlay();

	Tiles.SetNum(GridSize * GridSize);
	SpawnArena();
}
