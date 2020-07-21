// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DropPointUnit.h"
#include "DropPointUnitItem.generated.h"

/**
 * A basic struct used by the DropPoint game mode to store units in an item form for the inventory.
 */
USTRUCT(BlueprintType)
struct DROPPOINT_API FDropPointUnitItem
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = DropPoint, EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ADropPointUnit> UnitType;

	UPROPERTY(Category = DropPoint, EditAnywhere, BlueprintReadWrite)
	int32 Quantity =  0;

	UPROPERTY(Category = DropPoint, EditAnywhere, BlueprintReadWrite)
	int32 Cost = 0;

	FORCEINLINE UFUNCTION(Category = DropPoint, BlueprintSetter)
	void SetQuantity(const int32& Amount) { Quantity = Amount; };
};
