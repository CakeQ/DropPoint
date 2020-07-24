// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DropPointSpawnComponent.h"
#include "DropPointSpawnComponentCluster.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Category = DropPoint, meta = (BlueprintSpawnableComponent))
class DROPPOINT_API UDropPointSpawnComponentCluster : public UDropPointSpawnComponent
{
	GENERATED_BODY()
protected:
	UPROPERTY(Category = Classes, EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ADropPointTile> TileClass;

	UPROPERTY(Category = DropPoint, EditAnywhere, BlueprintReadWrite)
	bool bDiagonalsOnly = false;

	UPROPERTY(Category = DropPoint, EditAnywhere, BlueprintReadWrite)
	int32 ClusterChance = 25;

	UPROPERTY(Category = DropPoint, EditAnywhere, BlueprintReadWrite)
	int32 ClusterRange = 1;

public:
	virtual void Fire(ADropPointGameMode* OwnerMode, const FDropPointGridCoord& Coordinates) override;
};
