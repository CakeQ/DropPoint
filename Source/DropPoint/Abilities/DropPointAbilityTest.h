// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DropPointAbility.h"
#include "DropPointAbilityTest.generated.h"

/**
 * 
 */
UCLASS()
class DROPPOINT_API UDropPointAbilityTest : public UDropPointAbility
{
	GENERATED_BODY()
	
public:

	UDropPointAbilityTest();

	void BeginPlay() override;

	void Trigger(class ADropPointUnit* Owner) override;
};
