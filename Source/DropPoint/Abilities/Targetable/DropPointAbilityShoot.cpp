// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.


#include "DropPointAbilityShoot.h"
#include "DropPointUnit.h"
#include "Tiles/DropPointTile.h"

void UDropPointAbilityShoot::Trigger(ADropPointUnit* Owner)
{
	Super::Trigger(Owner);

	if(!TargetTile)
	{
		return;
	}

	ADropPointUnit* TargetUnit = TargetTile->GetUnit(Owner->GetLayer());

	if(!TargetUnit)
	{
		return;
	}
	
	TargetUnit->TakeDamage(DamageAmount);
}
