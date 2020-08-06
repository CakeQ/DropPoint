// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.


#include "DropPointAbilityMove.h"
#include "Tiles/DropPointTile.h"

void UDropPointAbilityMove::Trigger(ADropPointUnit* Owner)
{
	if(!TargetTile || !TargetTile->SetUnit(Owner, false))
	{
		return;
	}
	
	Super::Trigger(Owner);
}
