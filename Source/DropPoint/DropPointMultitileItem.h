// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DropPointGridCoord.h"
#include "DropPointMultitileItem.generated.h"

/**
* A basic struct used by the DropPoint game mode to store a tile type and its possible spawn chances.
*/
USTRUCT(BlueprintType)
struct DROPPOINT_API FDropPointMultitileItem
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = DropPoint, EditInstanceOnly, BlueprintReadOnly)
	FDropPointGridCoord OffsetCoords;

	UPROPERTY(Category = DropPoint, EditInstanceOnly, BlueprintReadOnly)
	float OffsetRotation;

	UPROPERTY(Category = Classes, EditInstanceOnly, BlueprintReadOnly)
	TSubclassOf<class ADropPointTile> TileClass;
};
