// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "DropPointEnums.generated.h"

/**
 * 
 */
UENUM()
enum class ETileFlags : uint8
{
	None,
	Highlighted = 0x01,
	Selected = 0x02,
	IncomingUnit = 0x04,
	IncomingDamage = 0x08,
	HasMinerals = 0x16
};
ENUM_CLASS_FLAGS(ETileFlags)

UENUM()
enum class EUnitFlags : uint8
{
	None,
	TakingOff = 0x01,
	Overheating = 0x02,
	Invulnerable = 0x04
};
ENUM_CLASS_FLAGS(EUnitFlags)

UENUM()
enum class EUnitFactions : uint8
{
	Player,
	Neutral,
	Hostile
};

UENUM()
enum class EUnitLayers : uint8
{
	Ground,
	Flying,
	Environmental
};
