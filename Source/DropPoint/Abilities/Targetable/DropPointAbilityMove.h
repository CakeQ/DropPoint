// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/DropPointAbilityTarget.h"
#include "DropPointAbilityMove.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class DROPPOINT_API UDropPointAbilityMove : public UDropPointAbilityTarget
{
	GENERATED_BODY()

	virtual void Trigger(ADropPointUnit* Owner) override;
};
