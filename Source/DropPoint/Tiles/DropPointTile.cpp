// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#include "DropPointTile.h"
#include "DropPointUnit.h"
#include "DropPointGridCoord.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstance.h"
#include "UObject/ConstructorHelpers.h"

ADropPointTile::ADropPointTile()
{
	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileMesh0"));
	RootComponent = TileMesh;
}

void ADropPointTile::SetTileCoords(const FDropPointGridCoord& NewCoord)
{
	TileCoordinates = NewCoord;
	TileMesh->SetScalarParameterValueOnMaterials(TEXT("TileX"), TileCoordinates.x);
	TileMesh->SetScalarParameterValueOnMaterials(TEXT("TileY"), TileCoordinates.y);
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

void ADropPointTile::SetUnit(ADropPointUnit* NewUnit, bool bForce = false)
{
	for (ADropPointUnit* Unit : Units)
	{
		if (Unit->GetLayer() == NewUnit->GetLayer() && !bForce)
		{
			if (!bForce)
			{
				return;
			}
			Units.Remove(Unit);
		}
	}
	Units.Add(NewUnit);
	NewUnit->SetConnectedTile(this);
	NewUnit->SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, 50.0f));
}

ADropPointUnit* ADropPointTile::GetUnit(EUnitLayers Layer = EUnitLayers::Ground)
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

void ADropPointTile::SetTileFlag(const ETileFlags& Value)
{
	TileFlags = (uint8)Value;
}

void ADropPointTile::AddTileFlag(const ETileFlags& Value)
{
	TileFlags |= (uint8)Value;
}

void ADropPointTile::RemoveTileFlag(const ETileFlags& Value)
{
	TileFlags &= ~(uint8)Value;
}

bool ADropPointTile::HasTileFlag(const ETileFlags& Value)
{
	return TileFlags & (uint8)Value;
}

