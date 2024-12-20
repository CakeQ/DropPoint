// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2019  All Rights Reserved.

#include "DropPointGameMode.h"



#include "AABB.h"
#include "AABB.h"
#include "AABB.h"
#include "AABB.h"
#include "AABB.h"
#include "AABB.h"
#include "AABB.h"
#include "AABB.h"
#include "DropPointGridCoord.h"
#include "DropPointPlayerController.h"
#include "DropPointCharacter.h"
#include "DropPointUnit.h"
#include "DropPointAbility.h"
#include "Widgets/DropPointWidgetTurn.h"
#include "Widgets/DropPointWidgetLevelDebug.h"
#include "Tiles/DropPointTile.h"
#include "CoreMinimal.h"
#include "TextLocalizationResource.h"
#include "Engine/World.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Actor.h"
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
			OnEndTurn.AddDynamic(TurnCountWidget, &UDropPointWidgetTurn::UpdateTurn);
		}
	}

	if(LevelDebugWidgetClass)
	{
		UDropPointWidgetLevelDebug* DebugWidget = CreateWidget<UDropPointWidgetLevelDebug>(GetWorld(), LevelDebugWidgetClass);
		DebugWidget->SetGameMode(this);
		DebugWidget->AddToViewport();
	}
	
	// Init tile indexed array size
	Tiles.SetNum(GridSize* GridSize);

	// Set level seed
	FMath::SRandInit(FTextLocalizationResource::HashString(*LevelSeed));

	// Calculate grid offset
	GridOffset = floor(((GridSize * TileSize) / 2) / 100) * 100;

	SpawnArena();

	for (ADropPointUnit* Unit : GetUnits())
	{
		if (Unit->GetFaction() == PlayerCharacter->GetFaction())
		{
			PlayerCharacter->AddUnit(Unit);
		}
	}
}

int32 ADropPointGameMode::GetLinearIndex(const FDropPointGridCoord& Coord) const
{
	return (Coord.GridY * GridSize) + Coord.GridX;
}

int32 ADropPointGameMode::IsInLinearRange(const int32& Index, const int32& Size)
{
	if (Index >= 0 && Index <= (((Size - 1) * Size) + (Size - 1)))
	{
		return true;
	}
	return false;
}

void ADropPointGameMode::SetTilePos(const FDropPointGridCoord& Coord, ADropPointTile* Tile)
{
	check(IsInsideArena(Coord));
	const int32 Index = GetLinearIndex(Coord);
	check(IsInLinearRange(Index, GridSize));
	Tile->SetTileCoords(Coord);
	Tiles[Index] = Tile;
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
	return GetTileAtPos(Origin + Offset);
}

TArray<ADropPointTile*> ADropPointGameMode::GetTileORange(const FDropPointGridCoord& Origin, const int32& Range, const bool& bRadial = false) const
{
	return GetTileRange(Origin, Range,  bRadial, false);
}

TArray<ADropPointTile*> ADropPointGameMode::GetTileRange(const FDropPointGridCoord& Origin, const int32& Range, const bool& bRadial = false, const bool& bIncludeOrigin = true) const
{
	TArray<ADropPointTile*> Ret;
	
	const FVector OriginVector = FVector(Origin.GridX, Origin.GridY, 0);
	for(int i = -Range; i <= Range; i++)
	{
		for(int j = -Range; j <= Range; j++)
		{
			FDropPointGridCoord Coord = Origin + FDropPointGridCoord(i, j);
			if(IsInLinearRange(GetLinearIndex(Coord), GridSize))
			{
				if(Coord == Origin && !bIncludeOrigin)
				{
					continue;
				}
				if(bRadial)
				{
					const float DistToCenter = round(FVector::DistXY(FVector(Coord.GridX, Coord.GridY, 0), OriginVector));
					if(DistToCenter > Range)
					{
						continue;
					}
				}
				ADropPointTile* Tile = GetTileAtPos(Coord);
				if(Tile)
				{
					Ret.Add(Tile);
				}
			}
		}
	}

	return Ret;
}

TArray<FDropPointGridCoord> ADropPointGameMode::GetCoordORange(const FDropPointGridCoord& Origin, const int32& Range, const bool& bRadial = false) const
{
	return GetCoordRange(Origin, Range, bRadial, false);
}

TArray<FDropPointGridCoord> ADropPointGameMode::GetCoordRange(const FDropPointGridCoord& Origin, const int32& Range, const bool& bRadial = false, const bool& bIncludeOrigin = true) const
{
	TArray<FDropPointGridCoord> Ret;
	
	const FVector OriginVector = FVector(Origin.GridX, Origin.GridY, 0);
	for(int i = -Range; i <= Range; i++)
	{
		for(int j = -Range; j <= Range; j++)
		{
			FDropPointGridCoord Coord = Origin + FDropPointGridCoord(i, j);
			if(IsInLinearRange(GetLinearIndex(Coord), GridSize))
			{
				if(Coord == Origin && !bIncludeOrigin)
				{
					continue;
				}
				if(bRadial)
				{
					const float DistToCenter = round(FVector::DistXY(FVector(Coord.GridX, Coord.GridY, 0), OriginVector));
					if(DistToCenter > Range)
					{
						continue;
					}
				}
				Ret.Add(Coord);
			}
		}
	}

	return Ret;
}

bool ADropPointGameMode::SetTileUnit(const FDropPointGridCoord& Coord, ADropPointUnit* Unit, const bool bForce = false) const
{
	if (!IsInsideArena(Coord))
	{
		return false;
	}
	ADropPointTile* RefTile = GetTileAtPos(Coord);

	return RefTile->SetUnit(Unit, bForce);
}

bool ADropPointGameMode::TileHasUnit(const FDropPointGridCoord& Coord, const EUnitLayers& Layer = EUnitLayers::Ground) const
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
	if (Coord.GridX >= 0 && Coord.GridX < GridSize)
	{
		if (Coord.GridY >= 0 && Coord.GridY < GridSize)
		{
			return true;
		}
	}
	return false;
}

ADropPointUnit* ADropPointGameMode::CreateUnit(const FDropPointGridCoord& Coord, TSubclassOf<ADropPointUnit>& UnitType, EUnitFactions& Faction, const bool bForce = false)
{
	if (!UnitType || !IsInsideArena(Coord))
	{
		return nullptr;
	}

	ADropPointTile* RefTile = GetTileAtPos(Coord);
	if (RefTile->HasUnit(UnitType->GetDefaultObject<ADropPointUnit>()->GetLayer()) && !bForce)
	{
		return nullptr;
	}

	ADropPointUnit* NewUnit = GetWorld()->SpawnActor<ADropPointUnit>(UnitType);
	NewUnit->SetFaction(Faction);
	if (NewUnit->HasUnitFlag(EUnitFlags::Core) && Units.Num())
	{
		for (ADropPointUnit* LoopUnit : Units)
		{
			if (LoopUnit->GetFaction() == NewUnit->GetFaction())
			{
				LoopUnit->SetCore(NewUnit);
			}
		}
	}
	else if (Units.Num())
	{
		for (ADropPointUnit* ExistingUnit : Units)
		{
			if (ExistingUnit->HasUnitFlag(EUnitFlags::Core) && ExistingUnit->GetFaction() == NewUnit->GetFaction())
			{
				NewUnit->SetCore(ExistingUnit);
				break;
			}
		}
	}

	if (!SetTileUnit(Coord, NewUnit, bForce) && NewUnit)
	{
		NewUnit->DestroyUnit();
		return nullptr;
	}

	if (NewUnit)
	{
		Units.Add(NewUnit);
		NewUnit->PostCreateUnit(this);
	}

	return NewUnit;
}

void ADropPointGameMode::RemoveUnit(ADropPointUnit* UnitToRemove, const bool SkipFollowUpSpawn)
{
	if (ADropPointTile* ConnectedTile = UnitToRemove->GetConnectedTile())
	{
		ConnectedTile->RemoveUnit(UnitToRemove);
	}
	Units.Remove(UnitToRemove);
	//if (UnitToRemove->FollowUpUnit != nullptr && !SkipFollowUpSpawn)
	//{
	//	CreateUnit(UnitToRemove->GetUnitCoordinates(), UnitToRemove->FollowUpUnit, UnitToRemove->GetFaction());
	//}
}

ADropPointTile* ADropPointGameMode::CreateTile(const FDropPointGridCoord& Coord, const TSubclassOf<class ADropPointTile>& TileType, const bool bForce = false)
{
	const float XOffset = (Coord.GridX * TileSize) - GridOffset; // Divide by dimension
	const float YOffset = ((Coord.GridY % GridSize) * TileSize) - GridOffset; // Modulo gives remainder

	// Make position vector, offset from Grid location
	const FVector BlockLocation = FVector(XOffset, YOffset, 0.f);

	// Get reference to any existing tiles at the coord.
	ADropPointTile* ExistingTile = GetTileAtPos(Coord);

	// Because the default object doesn't work here, we need to create the tile before checking for existing tiles.
	ADropPointTile* NewTile = GetWorld()->SpawnActor<ADropPointTile>(TileType, BlockLocation, FRotator(0, 0, 0));

	if(ExistingTile)
	{
		if (ExistingTile->GetPriority() < NewTile->GetPriority() || bForce)
		{
			ExistingTile->DestroyTile(true);
		}
		else
		{
			NewTile->DestroyTile(true);
			return nullptr;
		}
	}

	if (NewTile)
	{
		SetTilePos(Coord, NewTile);
		NewTile->PostCreateTile(this);
	}

	return NewTile;
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

	OnEndTurn.Broadcast(++TurnCount);
}

TSubclassOf<ADropPointTile> ADropPointGameMode::PickTileFromPool(const float& DistToCenter)
{
	if (!TilePool.Num())
	{
		return nullptr;
	}

	// Generate a weighted array to pick a candidate from.
	TArray<int32> Pool;
	for (int32 Index = 0; Index < TilePool.Num(); Index++)
	{
		FDropPointPoolItem& PoolItem = TilePool[Index];
		const int32 ItemWeight = floor((PoolItem.GetWeight(DistToCenter)) * 100);

		for (int32 Counter = 0; Counter < ItemWeight; Counter++)
		{
			Pool.Add(Index);
		}
	}

	if (!Pool.Num())
	{
		return nullptr;
	}

	const int32 IndexToUse = round(FMath::SRand() * (Pool.Num() - 1));

	// Pick the candidate.
	return TilePool[Pool[IndexToUse]].TileClass;
}

void ADropPointGameMode::SetSeed(const FText& NewSeed)
{
	FMath::SRandInit(FTextLocalizationResource::HashString(*NewSeed.ToString()));
}

void ADropPointGameMode::SpawnArena()
{
	if (!TilePool.Num())
	{
		// The tile pool is empty! Get outta here!
		return;
	}

	// Get grid central coordinate. For use with distancing.
	const FVector GridCenter = FVector(GridSize / 2, GridSize / 2, 0);

	// Loop to spawn each block
	for (int32 BlockXIndex = 0; BlockXIndex < GridSize; BlockXIndex++)
	{
		for (int32 BlockYIndex = 0; BlockYIndex < GridSize; BlockYIndex++)
		{
			// Get distance to center, for positional spawn pool bonuses.
			const float DistToCenter = round(FVector::DistXY(FVector(BlockXIndex, BlockYIndex, 0), GridCenter));
			const TSubclassOf<ADropPointTile>& TileTypeClass = PickTileFromPool(DistToCenter);
			CreateTile(FDropPointGridCoord(BlockXIndex, BlockYIndex), TileTypeClass, false);
		}
	}
}

void ADropPointGameMode::ClearArena()
{
	if(!Tiles.Num())
	{
		return;
	}
	for(ADropPointTile* Tile : Tiles)
	{
		Tile->DestroyTile(true);
	}
	Tiles.Empty();
	Units.Empty();
}

void ADropPointGameMode::RegenerateArena()
{
	ClearArena();
	Tiles.SetNum(GridSize * GridSize);
	SpawnArena();
}
