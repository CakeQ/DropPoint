// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2019  All Rights Reserved.

#include "DropPointGameMode.h"
#include "DropPointGridCoord.h"
#include "DropPointPlayerController.h"
#include "DropPointCharacter.h"
#include "DropPointUnit.h"
#include "DropPointAbility.h"
#include "Widgets/DropPointWidgetTurn.h"
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

int32 ADropPointGameMode::GetLinearIndex(const FDropPointGridCoord& Coord) const
{
	return (Coord.y * GridSize) + Coord.x;
}

int32 ADropPointGameMode::IsInLinearRange(const int32& Index, const int32& Size) const
{
	if (Index >= 0 && Index <= (((Size - 1) * Size) + (Size - 1)))
	{
		return true;
	}
	return false;
}

void ADropPointGameMode::SetTilePos(const FDropPointGridCoord& Coord, ADropPointTileInteractive* tile)
{
	check(IsInsideArena(Coord));
	const int32 Index = GetLinearIndex(Coord);
	check(IsInLinearRange(Index, GridSize));
	tile->SetTileCoords(Coord);
	Tiles[Index] = tile;
}

ADropPointTile* ADropPointGameMode::GetTileAtPos(const FDropPointGridCoord& Coord) const
{
	if (IsInsideArena(Coord))
	{
		const int32 Index = GetLinearIndex(Coord);
		check(Index >= 0 && Index < Tiles.Num());
		return Tiles[Index];
	}
	return nullptr;
}

ADropPointTile* ADropPointGameMode::GetTileStep(const FDropPointGridCoord& Origin, const FDropPointGridCoord& Offset) const
{
	FDropPointGridCoord newCoords;
	newCoords.x = origin.x + offset.x;
	newCoords.y = origin.y + offset.y;
	return GetTileAtPos(newCoords);
}

void ADropPointGameMode::SetTileUnit(const FDropPointGridCoord& Coord, ADropPointUnit* Unit, bool bForce = false)
{
	if (!IsInsideArena(Coord))
	{
		return;
	}
	ADropPointTile* RefTile = GetTileAtPos(Coord);
	if (RefTile->HasUnit(NewUnit->GetLayer()) && !bForce)
	{
		return;
	}
	RefTile->SetUnit(NewUnit, bForce);
}

bool ADropPointGameMode::TileHasUnit(const FDropPointGridCoord& Coord, EUnitLayers Layer = EUnitLayers::Ground) const
{
	if (!IsInsideArena(Coord))
	{
		return false;
	}
	ADropPointTile* RefTile = GetTileAtPos(Coord);
	if (RefTile->HasUnit(Layer))
	{
		return true;
	}
	return false;
}

bool ADropPointGameMode::IsInsideArena(const FDropPointGridCoord& Coord) const
{
	if (Coord.x >= 0 && Coord.x < GridSize)
	{
		if (Coord.y >= 0 && Coord.y < GridSize)
		{
			return true;
		}
	}
	return false;
}

void ADropPointGameMode::CreateUnit(const FDropPointGridCoord& Coord, TSubclassOf<ADropPointUnit> UnitType, EUnitFactions Faction, bool bForce = false)
{
	if (!UnitType || !IsInsideArena(Coord))
	{
		return;
	}

	ADropPointTile* RefTile = GetTileAtPos(Coord);
	if (RefTile->HasUnit(UnitType->GetDefaultObject<ADropPointUnit>()->GetLayer()) && !bForce)
	{
		return;
	}

	ADropPointUnit* NewUnit = GetWorld()->SpawnActor<ADropPointUnit>(UnitType);
	NewUnit->SetFaction(Faction);
	Units.Add(NewUnit);
	SetTileUnit(Coord, NewUnit, bForce);
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
