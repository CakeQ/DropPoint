// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.


#include "DropPointSpawnComponentUnit.h"
#include "DropPointGameMode.h"
#include "DropPointUnit.h"

void UDropPointSpawnComponentUnit::Fire(class ADropPointGameMode* OwnerMode, const FDropPointGridCoord& Coordinates)
{
	Super::Fire(OwnerMode, Coordinates);

	if (UnitSpawnTypeClasses.Num())
	{
		OwnerMode->CreateUnit(Coordinates, UnitSpawnTypeClasses[round(FMath::SRand() * (UnitSpawnTypeClasses.Num() - 1))], UnitSpawnFaction, true);
	}
}
