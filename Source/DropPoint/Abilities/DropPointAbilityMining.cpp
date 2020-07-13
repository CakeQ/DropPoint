// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.


#include "DropPointAbilityMining.h"
#include "DropPointUnit.h"
#include "Tiles/DropPointTile.h"

UDropPointAbilityMining::UDropPointAbilityMining()
{

}

void UDropPointAbilityMining::Trigger(ADropPointUnit* Owner)
{
	Super::Trigger(Owner);

	ADropPointTile* RefTile = Owner->GetConnectedTile();
	if (RefTile->HasTileFlag(ETileFlags::HasMinerals))
	{
		Owner->AddResources(10);
	}
}