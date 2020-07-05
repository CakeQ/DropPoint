// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DropPointAbility.h"
#include "DropPointAbilityMining.generated.h"

/**
 * An ability that passively provides minerals to the unit if the unit is placed on a tile that contains minerals.
 */
UCLASS(Blueprintable, Category = Abilities, meta = (BlueprintSpawnableComponent))
class DROPPOINT_API UDropPointAbilityMining : public UDropPointAbility
{
	GENERATED_BODY()
	
public:
	UDropPointAbilityMining();

	/**
	 * Called when the ability component is selected to fire. Gives the unit minerals passively if the tile it sits on contains minerals.
	 * @param Owner - The unit to handle functionality with.
	 */
	void Trigger(class ADropPointUnit* Owner) override;
};
