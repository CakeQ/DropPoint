// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/DropPointAbilityTarget.h"
#include "DropPointAbilityShoot.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class DROPPOINT_API UDropPointAbilityShoot : public UDropPointAbilityTarget
{
	GENERATED_BODY()

protected:
	/** The amount of damage to deal to the target */
	UPROPERTY(Category = Ability, EditAnywhere, BlueprintReadWrite)
	int32 DamageAmount;
	
public:
	/**
	* Called when the ability component is selected to fire. Changes the material of the owning unit to the TestMaterial.
	* @param Owner - The unit to handle functionality with.
	*/
	virtual void Trigger(class ADropPointUnit* Owner) override;
};
