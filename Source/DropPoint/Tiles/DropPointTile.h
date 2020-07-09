// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2019  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DropPointEnums.h"
#include "DropPointGridCoord.h"
#include "DropPointTile.generated.h"

/**
 * Base type for the DropPoint game mode grid tile. Does not have any intractability, and should not be used within the arena. See DropPointTileInteractive.
 */
UCLASS()
class DROPPOINT_API ADropPointTile : public AActor
{
	GENERATED_BODY()

public:	
	ADropPointTile();

protected:
	/** Tile mesh */
	UPROPERTY(Category = References, EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* TileMesh;

	/** Units contained within the tile, with layering taken into account. There should only ever be one unit per layer. */
	UPROPERTY(Category = References, VisibleAnywhere, BlueprintReadWrite)
	TArray<class ADropPointUnit*> Units;

	/** Tile property flags. See EUnitFlags in DropPointEnums.h for flag descriptions. */
	UPROPERTY(Category = Tile, EditAnywhere, BlueprintReadWrite, meta = (Bitmask, BitmaskEnum = "ETileFlags"))
	uint8 TileFlags;

	/** Tile coordinates within the game grid */
	UPROPERTY(Category = Tile, VisibleAnywhere, BlueprintReadWrite)
	FDropPointGridCoord TileCoordinates;

public:	

	/**
	 * Set the unit to have only the input flag.
	 * @param Value - The input flag to set.
	 */
	UFUNCTION(Category = Tile, BlueprintCallable)
	void SetTileFlag(const ETileFlags& Value);

	/**
	 * Adds the input flag to the tile's flags.
	 * @param Value - The input flag to add.
	 */
	UFUNCTION(Category = Tile, BlueprintCallable)
	void AddTileFlag(const ETileFlags& Value);

	/**
	 * Removes the input flag from the tile's flags.
	 * @param Value - The input flag to remove.
	 */
	UFUNCTION(Category = Tile, BlueprintCallable)
	void RemoveTileFlag(const ETileFlags& Value);

	/**
	 * Checks to see if this tile has the input flag.
	 * @param Value - The flag to check.
	 */
	UFUNCTION(Category = Tile, BlueprintCallable)
	bool HasTileFlag(const ETileFlags& Value);

	/** Gets the tile's current grid coordinates. */
	FORCEINLINE UFUNCTION(Category = Tile, BlueprintGetter)
	FDropPointGridCoord& GetGridCoords() { return TileCoordinates; };

	/**
	 * Sets the tile to have the given coordinates within the grid.
	 * @param NewCoord - The coordinates to use.
	 */
	UFUNCTION(Category = Tile, BlueprintSetter)
	virtual void SetTileCoords(const FDropPointGridCoord& NewCoord);

	/**
	 * Checks to see if this tile has a unit in the given layer.
	 * @param Layer - The layer to check.
	 */
	UFUNCTION(Category = Tile, BlueprintCallable)
	bool HasUnit(EUnitLayers Layer);

	/**
	 * Sets the tile to have the input unit.
	 * @param NewUnit - The new unit to take ownership of. Takes layering into account.
	 * @param bForce - Will override and replace any existing unit if it exists on the same layer.
	 */
	UFUNCTION(Category = Tile, BlueprintCallable)
	void SetUnit(class ADropPointUnit* NewUnit, bool bForce);

	/**
	 * Checks to see if this tile has a unit in the given layer.
	 * @param Layer - The layer to check.
	 */
	UFUNCTION(Category = Tile, BlueprintCallable)
	ADropPointUnit* GetUnit(EUnitLayers Layer);
};
