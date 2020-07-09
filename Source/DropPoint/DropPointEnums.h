// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "DropPointEnums.generated.h"

/**
 * Tile property flags.
 * Highlighted - Highlighted by the cursor.
 * Selected - Selected by the player.
 * IncomingUnit - A new unit will be placed on this tile in the coming turns.
 * IncomingDamage - This tile and its contents will receive damage in the coming turns.
 * HasMinerals - This tile contains minerals.
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

/**
 * Unit property flags.
 * TakingOff - This unit is attempting to take off.
 * Overheating - This unit has overheated and is stunned.
 * Invulnerable - This unit is incapable of being damaged or destroyed.
 */
UENUM()
enum class EUnitFlags : uint8
{
	None = 0,
	TakingOff,
	Overheating,
	Invulnerable
};
ENUM_CLASS_FLAGS(EUnitFlags)

/**
 * Game factions.
 * Player - Controllable by the player.
 * Neutral - Environment, such as rocks, sandstorms, and any other environmental hazards.
 * Friendly - Will attempt to attack Hostile faction units. Friendly to the player.
 * Hostile - Will attempt to actively attack the player.
 */
UENUM()
enum class EUnitFactions : uint8
{
	Player,
	Neutral,
	Friendly,
	Hostile
};

/**
 * Unit layers.
 * Ground - On the ground.
 * Flying - Above the ground, should be flying above any ground units.
 * Environmental - For environmental hazards that need to encompass other units, such as sandstorms.
 */
UENUM()
enum class EUnitLayers : uint8
{
	Ground,
	Flying,
	Environmental
};

/**
 * Ability types.
 * Instant - Called as soon as the player triggers this ability.
 * Targetable - Called as soon as the player triggers this ability. Requires a selected target.
 * Passive - Called on turn end, all passive abilities fire between turns if they exist on a unit.
 */
UENUM()
enum class EAbilityTypes
{
    Instant,
    Targetable,
    Passive
};

/**
 * Ability categories. Mostly used for sorting within the UI.
 * Standard - Standard ability, owned by the unit.
 * Biome - Biome ability, shows up separately from standard abilities.
 */
UENUM()
enum class EAbilityCats
{
    Standard,
    Biome
};
