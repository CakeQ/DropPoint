// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2019  All Rights Reserved.

#include "DropPointGameMode.h"
#include "DropPointPlayerController.h"
#include "DropPointCharacter.h"
#include "DropPointWidgetTurn.h"
#include "Tiles/DropPointTile.h"
#include "Tiles/DropPointTileInteractive.h"
#include "CoreMinimal.h"
#include "Engine/World.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "Blueprint/UserWidget.h"

ADropPointGameMode::ADropPointGameMode()
{

}

void ADropPointGameMode::BeginPlay()
{
	Super::BeginPlay();
	//if (ArenaClass)
	//{
	//	ArenaController = GetWorld()->SpawnActor<ADropPointGameMode>(ArenaClass.GetDefaultObject()->GetClass(), FVector(0, 0, 0), FRotator(0, 0, 0));
	//}

	if (PlayerClass)
	{
		PlayerCharacter = GetWorld()->SpawnActor<ADropPointCharacter>(PlayerClass.GetDefaultObject()->GetClass(), FVector(-100.f, 100.f, 200.f), FRotator(0, -45.f, 0));
		GetWorld()->GetFirstPlayerController()->Possess(PlayerCharacter);
		PlayerCharacter->DisablePan();
	}

	if (TurnCountWidgetClass)
	{
		TurnCountWidget = CreateWidget<UDropPointWidgetTurn>(GetWorld(), TurnCountWidgetClass);
		if (TurnCountWidget)
		{
			TurnCountWidget->UpdateTurn(TurnCount);
			TurnCountWidget->AddToViewport();
		}
	}

	Tiles.SetNum(GridSize* GridSize);
	SpawnArena();
}

int32 ADropPointGameMode::GetLinearIndex(const FDropPointGridCoord& coord) const
{
	return (coord.y * GridSize) + coord.x;
}

int32 ADropPointGameMode::IsInLinearRange(const int32& linearIndex, const int32& size) const
{
	if (linearIndex >= 0 && linearIndex <= (((size - 1) * size) + (size - 1)))
	{
		return true;
	}
	return false;
}

void ADropPointGameMode::SetTilePos(const FDropPointGridCoord& coord, ADropPointTileInteractive* tile)
{
	check(IsInsideArena(coord));
	const int32 linearIndex = GetLinearIndex(coord);
	check(IsInLinearRange(linearIndex, GridSize));
	tile->SetTileCoords(coord);
	Tiles[linearIndex] = tile;
}

ADropPointTile* ADropPointGameMode::GetTileAtPos(const FDropPointGridCoord& coord) const
{
	if (IsInsideArena(coord))
	{
		const int32 linearIndex = GetLinearIndex(coord);
		check(linearIndex >= 0 && linearIndex < Tiles.Num());
		return Tiles[linearIndex];
	}
	return nullptr;
}

ADropPointTile* ADropPointGameMode::GetTileStep(const FDropPointGridCoord& origin, const FDropPointGridCoord& offset) const
{
	FDropPointGridCoord newCoords;
	newCoords.x = origin.x + offset.x;
	newCoords.y = origin.y + offset.y;
	return GetTileAtPos(newCoords);
}

void ADropPointGameMode::SetTileUnit(const FDropPointGridCoord& coord, AActor* NewUnit, bool Force = false)
{
	if (!IsInsideArena(coord))
	{
		return;
	}
	ADropPointTile* RefTile = GetTileAtPos(coord);
	if (RefTile->HasUnit() && !Force)
	{
		return;
	}
	RefTile->SetUnit(NewUnit, Force);
}

bool ADropPointGameMode::TileHasUnit(const FDropPointGridCoord& coord) const
{
	if (!IsInsideArena(coord))
	{
		return false;
	}
	ADropPointTile* RefTile = GetTileAtPos(coord);
	if (RefTile->HasUnit())
	{
		return true;
	}
	return false;
}

bool ADropPointGameMode::IsInsideArena(const FDropPointGridCoord& coord) const
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

void ADropPointGameMode::CreateUnit(const FDropPointGridCoord& coord, TSubclassOf<AActor> ClassType, bool Force = false)
{
	if (!ClassType || !IsInsideArena(coord))
	{
		return;
	}

	ADropPointTile* RefTile = GetTileAtPos(coord);
	if (RefTile->HasUnit() && !Force)
	{
		return;
	}

	AActor* NewUnit = GetWorld()->SpawnActor<AActor>(ClassType.GetDefaultObject()->GetClass());
	SetTileUnit(coord, NewUnit);
}

void ADropPointGameMode::EndTurn()
{
	//Launch Units
	//Unit Actions
	//Hazard Progression
	//Apply Damage
	TurnCount++;
	if (TurnCountWidget)
	{
		TurnCountWidget->UpdateTurn(TurnCount);
	}
}

void ADropPointGameMode::SpawnArena()
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
			const FVector blockLocation = FVector(XOffset, YOffset, 0.f);

			// Spawn a block
			ADropPointTileInteractive* newTile = GetWorld()->SpawnActor<ADropPointTileInteractive>(TileTypeClass.GetDefaultObject()->GetClass(), blockLocation, FRotator(0, 0, 0));

			// Tell the block about its owner
			if (newTile != nullptr)
			{
				FDropPointGridCoord tileCoord;
				tileCoord.x = (newTile->GetActorLocation().X + gridOffset) / TileSize;
				tileCoord.y = (newTile->GetActorLocation().Y + gridOffset) / TileSize;
				SetTilePos(tileCoord, newTile);
			}
		}
	}
}
