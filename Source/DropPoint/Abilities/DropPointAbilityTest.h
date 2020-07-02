// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DropPointAbility.h"
#include "DropPointAbilityTest.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Category = Abilities, meta = (BlueprintSpawnableComponent))
class DROPPOINT_API UDropPointAbilityTest : public UDropPointAbility
{
	GENERATED_BODY()
	
public:
	UDropPointAbilityTest();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unit)
	class UMaterialInstance* TestMaterial;

public:
	void Trigger(class ADropPointUnit* Owner) override;
};
