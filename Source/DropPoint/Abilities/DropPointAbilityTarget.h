// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DropPointAbility.h"
#include "DropPointCharacter.h"

#include "DropPointAbilityTarget.generated.h"

/**
 * 
 */
UCLASS(NotBlueprintable)
class DROPPOINT_API UDropPointAbilityTarget : public UDropPointAbility
{
	GENERATED_BODY()
	
public:
	UDropPointAbilityTarget();

protected:
	/** The target unit of this ability. */
	UPROPERTY(Category = References, VisibleInstanceOnly, BlueprintReadWrite)
	class ADropPointTile* TargetTile;
	
	/**
	 * Member storage for the Owner unit of this ability.
	 * Since targeting requires dynamic calls the owner needs to be stored unlike standard abilities.
	 */
	UPROPERTY(Category = References, VisibleInstanceOnly, BlueprintReadWrite)
	class ADropPointUnit* OwnerUnit;

public:
	/** Get target unit */
	FORCEINLINE UFUNCTION(Category = DropPoint, BlueprintGetter)
	ADropPointTile* GetTargetTile() const { return TargetTile; }

	/** Get owner unit */
	FORCEINLINE UFUNCTION(Category = DropPoint, BlueprintGetter)
	ADropPointUnit* GetOwnerUnit() const { return OwnerUnit; }

	/**
	* Sets this ability's target unit. Fires the ability's QueueTrigger.
	* @param NewTarget - The unit to set as the target.
	*/
	UFUNCTION(Category = DropPoint, BlueprintCallable)
	void SetTarget(class ADropPointTile* NewTarget);

	/**
	* Sets this ability's owner unit.
	* @param NewOwner - The unit to set as the target.
	*/
	FORCEINLINE UFUNCTION(Category = DropPoint, BlueprintSetter)
	void SetOwner(class ADropPointUnit* NewOwner) { OwnerUnit = NewOwner; };
};
