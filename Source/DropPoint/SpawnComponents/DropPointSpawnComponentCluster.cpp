// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#include "DropPointSpawnComponentCluster.h"
#include "DropPointGameMode.h"
#include "Tiles/DropPointTile.h"

void UDropPointSpawnComponentCluster::Fire(ADropPointGameMode* OwnerMode, const FDropPointGridCoord& Coordinates)
{
	for(const FDropPointGridCoord& Coord : OwnerMode->GetCoordORange(Coordinates, ClusterRange))
	{
		OwnerMode->CreateTile(Coord, TileClass, false);
	}
}
