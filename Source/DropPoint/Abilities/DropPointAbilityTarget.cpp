// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.


#include "DropPointAbilityTarget.h"
#include "DropPointGameMode.h"
#include "DropPointUnit.h"
#include "Tiles/DropPointTile.h"

UDropPointAbilityTarget::UDropPointAbilityTarget()
{

}

void UDropPointAbilityTarget::SetTarget(ADropPointTile* NewTarget)
{
	if(AbilityRange)
	{
		ADropPointGameMode* Gamemode = Cast<ADropPointGameMode>(GetWorld()->GetAuthGameMode());
		const TArray<ADropPointTile*> Tiles = Gamemode->GetTileORange(OwnerUnit->GetConnectedTile()->GetTileCoords(), AbilityRange, true);
		for(ADropPointTile* Tile : Tiles)
		{
			Tile->RemoveTileFlag(ETileFlags::Targeted);
		}
		if(!Tiles.Find(NewTarget))
		{
			return;
		}
	}
	TargetTile = NewTarget;
	QueueTrigger(OwnerUnit);
}
