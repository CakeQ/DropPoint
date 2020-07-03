// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "DropPointGridCoord.generated.h"

/**
 * A basic struct used by the DropPoint game mode to store grid coordinates.
 */
USTRUCT(BlueprintType)
struct DROPPOINT_API FDropPointGridCoord
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = Coordinates, EditAnywhere, BlueprintReadWrite)
	int32 x;

	UPROPERTY(Category = Coordinates, EditAnywhere, BlueprintReadWrite)
	int32 y;	
};
