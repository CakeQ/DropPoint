// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DropPointGridCoord.h"
#include "DropPointMultitileItem.generated.h"

/**
* A basic struct used by the DropPoint game mode to store a tile type for multi-tile generation, and its offset settings.
*/
USTRUCT(BlueprintType)
struct DROPPOINT_API FDropPointMultitileItem
{
	GENERATED_BODY()

public:
	/** Coordinates for this tile to offset from the origin tile. */
	UPROPERTY(Category = DropPoint, EditInstanceOnly, BlueprintReadOnly)
	FDropPointGridCoord OffsetCoords;

	/** The rotation that this tile will be offset by from the origin tile. */
	UPROPERTY(Category = DropPoint, EditInstanceOnly, BlueprintReadOnly)
	float OffsetRotation;

	/** The tile class to use. */
	UPROPERTY(Category = Classes, EditInstanceOnly, BlueprintReadOnly)
	TSubclassOf<class ADropPointTile> TileClass;
};
