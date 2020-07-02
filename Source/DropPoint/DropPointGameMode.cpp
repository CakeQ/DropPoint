// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2019  All Rights Reserved.

#include "DropPointGameMode.h"
#include "DropPointGridCoord.h"
#include "DropPointPlayerController.h"
#include "DropPointCharacter.h"
#include "DropPointUnit.h"
#include "DropPointAbility.h"
#include "DropPointWidgetTurn.h"
#include "Widgets/DropPointWidgetUnitMenu.h"
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

	if (PlayerClass)
	{
		PlayerCharacter = GetWorld()->SpawnActor<ADropPointCharacter>(PlayerClass, FVector(-100.f, 100.f, 200.f), FRotator(0, -45.f, 0));
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

	if (UnitMenuWidgetClass && UnitSpawnClasses.Num())
	{
		UnitMenuWidget = CreateWidget<UDropPointWidgetUnitMenu>(GetWorld(), UnitMenuWidgetClass);
		if (UnitMenuWidget)
		{
			UnitMenuWidget->CreateButtons(UnitSpawnClasses, PlayerCharacter);
			UnitMenuWidget->AddToViewport();
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

void ADropPointGameMode::SetTileUnit(const FDropPointGridCoord& coord, ADropPointUnit* NewUnit, bool bForce = false)
{
	if (!IsInsideArena(coord))
	{
		return;
	}
	ADropPointTile* RefTile = GetTileAtPos(coord);
	if (RefTile->HasUnit(NewUnit->GetLayer()) && !bForce)
	{
		return;
	}
	RefTile->SetUnit(NewUnit, bForce);
}

bool ADropPointGameMode::TileHasUnit(const FDropPointGridCoord& coord, EUnitLayers Layer = EUnitLayers::Ground) const
{
	if (!IsInsideArena(coord))
	{
		return false;
	}
	ADropPointTile* RefTile = GetTileAtPos(coord);
	if (RefTile->HasUnit(Layer))
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

void ADropPointGameMode::CreateUnit(const FDropPointGridCoord& coord, TSubclassOf<ADropPointUnit> UnitType, bool bForce = false)
{
	if (!UnitType || !IsInsideArena(coord))
	{
		return;
	}

	ADropPointTile* RefTile = GetTileAtPos(coord);
	if (RefTile->HasUnit(UnitType->GetDefaultObject<ADropPointUnit>()->GetLayer()) && !bForce)
	{
		return;
	}

	ADropPointUnit* NewUnit = GetWorld()->SpawnActor<ADropPointUnit>(UnitType);
	Units.Add(NewUnit);
	SetTileUnit(coord, NewUnit, bForce);
}

void ADropPointGameMode::EndTurn()
{
	/* Sort the units list each turn so that all factions have their units done in order
	(should be friendly, neutral, then enemy unless changed), with each faction's units ordered by oldest to newest  */
	Units.Sort(ADropPointUnit::FactionPredicate);

	for (ADropPointUnit* Unit : Units)
	{
		// Handle all unit takeoffs
		if (Unit->HasUnitFlag(EUnitFlags::TakingOff))
		{
			Unit->TryLaunch();
		}

		// Call any passive abilities
		Unit->TriggerAbilities();
	}

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
			ADropPointTileInteractive* newTile = GetWorld()->SpawnActor<ADropPointTileInteractive>(TileTypeClass, blockLocation, FRotator(0, 0, 0));

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
