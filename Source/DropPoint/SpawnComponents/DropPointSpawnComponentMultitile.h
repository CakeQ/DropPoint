// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DropPointSpawnComponent.h"
#include "DropPointEnums.h"
#include "DropPointMultitileItem.h"
#include "DropPointSpawnComponentMultitile.generated.h"

/**
 * A spawn component that spawns a set of tiles around the parent actor based on an array of predefined tiles and offsets.
 */
UCLASS(Blueprintable, Category = DropPoint, meta = (BlueprintSpawnableComponent))
class DROPPOINT_API UDropPointSpawnComponentMultitile : public UDropPointSpawnComponent
{
	GENERATED_BODY()
	
protected:
	/** The array that stores all the multi-tile items to spawn. */
	UPROPERTY(Category = Classes, EditAnywhere, BlueprintReadWrite)
	TArray<FDropPointMultitileItem> Tiles;

public:
	/**
	 * Spawns all the multi-tile items.
	 * @param OwnerMode - The owner gamemode to send spawn information to.
	 * @param Coordinates - The origin coordinates of the parent actor.
	 */
	virtual void Fire(class ADropPointGameMode* OwnerMode, const FDropPointGridCoord& Coordinates) override;
};
