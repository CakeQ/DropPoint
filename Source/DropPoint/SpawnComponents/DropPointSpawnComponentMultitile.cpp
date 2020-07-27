// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.


#include "DropPointSpawnComponentMultitile.h"
#include "DropPointGameMode.h"

void UDropPointSpawnComponentMultitile::Fire(class ADropPointGameMode* OwnerMode, const FDropPointGridCoord& Coordinates)
{
	Super::Fire(OwnerMode, Coordinates);

	if (!Tiles.Num())
	{
		return;
	}

	for(const FDropPointMultitileItem& Item : Tiles)
	{
		FDropPointGridCoord NewCoords = Coordinates + Item.OffsetCoords;
		OwnerMode->CreateTile(NewCoords, Item.TileClass, false);
	}
}
