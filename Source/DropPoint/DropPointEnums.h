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
	None = 0,
	Highlighted,
	Selected,
	IncomingUnit,
	IncomingDamage,
	HasMinerals
};
ENUM_CLASS_FLAGS(ETileFlags)

UENUM()
enum class EUnitFlags : uint8
{
	None = 0,
	TakingOff,
	Overheating,
	Invulnerable
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

UENUM()
enum class EAbilityTypes
{
	Instant,
	Passive
};
