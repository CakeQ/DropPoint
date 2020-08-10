// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#include "DropPointTile.h"
#include "DropPointUnit.h"
#include "DropPointSpawnComponent.h"
#include "DropPointGridCoord.h"
#include "Components/StaticMeshComponent.h"

ADropPointTile::ADropPointTile()
{
	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileMesh0"));
	RootComponent = TileMesh;
}

void ADropPointTile::SetTileCoords(const FDropPointGridCoord& NewCoord)
{
	TileCoordinates = NewCoord;
	TileMesh->SetScalarParameterValueOnMaterials(TEXT("TileX"), TileCoordinates.GridX);
	TileMesh->SetScalarParameterValueOnMaterials(TEXT("TileY"), TileCoordinates.GridY);
}

bool ADropPointTile::HasUnit(EUnitLayers Layer = EUnitLayers::Ground)
{
	for (ADropPointUnit* Unit : Units)
	{
		if (Unit->GetLayer() == Layer)
		{
			return true;
		}
	}
	return false;
}

bool ADropPointTile::SetUnit(ADropPointUnit* NewUnit, const bool bForce = false)
{
	for (ADropPointUnit* Unit : Units)
	{
		if (Unit->GetLayer() == NewUnit->GetLayer())
		{
			if (!bForce)
			{
				return false;
			}
			Units.Remove(Unit);
			GetWorld()->DestroyActor(Unit);
		}
	}
	if(NewUnit->GetConnectedTile())
	{
		ADropPointTile* OldTile = NewUnit->GetConnectedTile();
		OldTile->RemoveUnit(NewUnit);
	}
	Units.Add(NewUnit);
	NewUnit->SetConnectedTile(this);
	NewUnit->SetUnitCoords(TileCoordinates);
	NewUnit->SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, 50.0f));
	return true;
}

bool ADropPointTile::RemoveUnit(ADropPointUnit* Unit)
{
	if(!Units.Find(Unit))
	{
		return false;
	}
	Units.Remove(Unit);
	return true;
}

ADropPointUnit* ADropPointTile::GetUnit(const EUnitLayers Layer = EUnitLayers::Ground)
{
	for (ADropPointUnit* Unit : Units)
	{
		if (Unit->GetLayer() == Layer)
		{
			return Unit;
		}
	}
	return nullptr;
}

void ADropPointTile::PostCreateTile(ADropPointGameMode* OwnerMode) const
{
	TArray<UDropPointSpawnComponent*> LogicComponents;
	GetComponents<UDropPointSpawnComponent>(LogicComponents);
	for (UDropPointSpawnComponent* LogicComponent : LogicComponents)
	{
		LogicComponent->Fire(OwnerMode, GetTileCoords());
	}
}

bool ADropPointTile::DestroyTile(const bool bUnits)
{
	if(bUnits && Units.Num())
	{
		for(ADropPointUnit* Unit : Units)
		{
			Unit->DestroyUnit();
		}
	}
	return GetWorld()->DestroyActor(this);
}

void ADropPointTile::UpdateMaterialVisuals()
{
	
}

void ADropPointTile::SetTileFlag(const ETileFlags& Value)
{
	TileFlags = (uint8)Value;
	UpdateMaterialVisuals();
}

void ADropPointTile::AddTileFlag(const ETileFlags& Value)
{
	TileFlags |= (uint8)Value;
	UpdateMaterialVisuals();
}

void ADropPointTile::RemoveTileFlag(const ETileFlags& Value)
{
	TileFlags &= ~(uint8)Value;
	UpdateMaterialVisuals();
}

bool ADropPointTile::HasTileFlag(const ETileFlags& Value) const
{
	return TileFlags & (uint8)Value;
}
