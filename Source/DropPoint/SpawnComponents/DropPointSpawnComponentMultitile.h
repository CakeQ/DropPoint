// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DropPointSpawnComponent.h"
#include "DropPointEnums.h"
#include "DropPointMultitileItem.h"
#include "DropPointSpawnComponentMultitile.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Category = DropPoint, meta = (BlueprintSpawnableComponent))
class DROPPOINT_API UDropPointSpawnComponentMultitile : public UDropPointSpawnComponent
{
	GENERATED_BODY()
	
protected:
	/** The current unit type class that will be spawned. */
	UPROPERTY(Category = Classes, EditAnywhere, BlueprintReadWrite)
	TArray<FDropPointMultitileItem> Tiles;

public:
	virtual void Fire(class ADropPointGameMode* OwnerMode, const FDropPointGridCoord& Coordinates) override;
};
