// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DropPointAbility.h"
#include "DropPointAbilityTest.generated.h"

/**
 * A test ability that changes the material of a unit on trigger.
 */
UCLASS(Blueprintable, Category = Abilities, meta = (BlueprintSpawnableComponent))
class DROPPOINT_API UDropPointAbilityTest : public UDropPointAbility
{
	GENERATED_BODY()
	
public:
	UDropPointAbilityTest();

protected:
	UPROPERTY(Category = Classes, EditAnywhere, BlueprintReadWrite)
	class UMaterialInstance* TestMaterial;

public:
	/**
	 * Called when the ability component is selected to fire. Changes the material of the owning unit to the TestMaterial.
	 * @param Owner - The unit to handle functionality with.
	 */
	void Trigger(class ADropPointUnit* Owner) override;
};
