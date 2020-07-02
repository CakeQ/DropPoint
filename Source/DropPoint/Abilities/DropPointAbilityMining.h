// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DropPointAbility.h"
#include "DropPointAbilityMining.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Category = Abilities, meta = (BlueprintSpawnableComponent))
class DROPPOINT_API UDropPointAbilityMining : public UDropPointAbility
{
	GENERATED_BODY()
	
public:

	UDropPointAbilityMining();

	void Trigger(class ADropPointUnit* Owner) override;
};
