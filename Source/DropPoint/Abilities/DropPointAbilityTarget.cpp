// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.


#include "DropPointAbilityTarget.h"

UDropPointAbilityTarget::UDropPointAbilityTarget()
{

}

void UDropPointAbilityTarget::SetTarget(ADropPointTile* NewTarget)
{
	TargetTile = NewTarget;
	QueueTrigger(OwnerUnit);
}
