// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2019  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DropPointEnums.h"
#include "DropPointGridCoord.h"
#include "DropPointPoolItem.h"
#include "GameFramework/Actor.h"
#include "GameFramework/GameModeBase.h"
#include "DropPointGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEndTurnDelegate, const int32&, NewCount);

/** The DropPoint Game mode. This handles the game grid, tiles, units, tile/unit spawning, and turn progression. It also sets up the UI with referenced values.*/
UCLASS(minimalapi)
class ADropPointGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADropPointGameMode();

protected:

	/** Player class */
	UPROPERTY(Category = Classes, EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> PlayerClass;

	/** Widget used to display the current turn count. */
	UPROPERTY(Category = Classes, EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UUserWidget> TurnCountWidgetClass;

	/** The pool of tiles that will be used by the arena generator. */
	UPROPERTY(Category = Classes, EditDefaultsOnly, BlueprintReadOnly)
	TArray<FDropPointPoolItem> TilePool;

	/** Reference to the player character. */
	UPROPERTY(Category = References, VisibleInstanceOnly, BlueprintReadWrite)
	class ADropPointCharacter* PlayerCharacter;

	/** Reference to the turn tracking widget. */
	UPROPERTY(Category = References, VisibleInstanceOnly, BlueprintReadOnly)
	class UDropPointWidgetTurn* TurnCountWidget;

	/** Linearly indexed array of the entire game grid's tiles.*/
	UPROPERTY(Category = References, VisibleInstanceOnly, BlueprintReadOnly)
	TArray<class ADropPointTile*> Tiles;

	/** List of all units in the game. */
	UPROPERTY(Category = References, VisibleInstanceOnly, BlueprintReadWrite)
	TArray<class ADropPointUnit*> Units;

	/** Current turn in the game. */
	UPROPERTY(Category = DropPoint, EditAnywhere, BlueprintReadWrite)
	int32 TurnCount = 0;

	/** The length and width of the arena that will be generated, in tiles. */
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadWrite)
	int32 GridSize = 7;

	/** The grid offset of the arena that will be generated, in UE4 units. */
	UPROPERTY(Category = Grid, VisibleInstanceOnly, BlueprintReadOnly)
	int32 GridOffset = 0;

	/** The size (in UE4 units) that each tile within the grid will occupy. */
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadWrite)
	float TileSize = 100.0f;

	/** The random seed used to generate the level with. */
	UPROPERTY(Category = Grid, EditDefaultsOnly, BlueprintReadOnly)
	FString LevelSeed;

	/** WIP: The core unit this unit is connected to. Should be replaced with the pylon network when possible. */
	class ADropPointUnit* ConnectedCore;

public:
	/** Delegate binding for turn ending. */
	UPROPERTY(Category = DropPoint, BlueprintAssignable)
	FEndTurnDelegate OnEndTurn;

	virtual void BeginPlay() override;

	/** 
	 * Gets the linear index value of the coordinate passed through.
	 * @param Coord - The X and Y values of the desired Coordinate.
	 */
	UFUNCTION(Category = Grid, BlueprintCallable)
	int32 GetLinearIndex(const FDropPointGridCoord& Coord) const;

	/**
	 * Checks to see if the linear index value is within the given size value.
	 * @param Index - The linear index value to check.
	 * @param Size - The grid size to compare with.
	 */
	UFUNCTION(Category = Grid, BlueprintCallable)
	static int32 IsInLinearRange(const int32& Index, const int32& Size);

	/**
	 * Sets a referenced tile at the given coordinates.
	 * @param Coord - The X and Y values of the desired Coordinate.
	 * @param Tile - The referenced tile to move.
	 */
	UFUNCTION(Category = Grid, BlueprintCallable)
	void SetTilePos(const FDropPointGridCoord& Coord, class ADropPointTile* Tile);

	/**
	 * Returns the tile at the given coordinates, if it exists.
	 * @param Coord - The X and Y values of the desired Coordinate.
	 */
	UFUNCTION(Category = Grid, BlueprintCallable)
	class ADropPointTile* GetTileAtPos(const FDropPointGridCoord& Coord) const;

	/**
	 * Returns the tile at the offset coordinates, if it exists.
	 * @param Origin - The origin coordinates.
	 * @param Offset - The amount to offset the origin by.
	 */
	UFUNCTION(Category = Grid, BlueprintCallable)
	class ADropPointTile* GetTileStep(const FDropPointGridCoord& Origin, const FDropPointGridCoord& Offset) const;

	/**
	* Returns an array of tiles around the origin coordinates, excluding the origin tile.
	* @param Origin - The origin coordinates.
	* @param Range - The range to iterate through.
	*/
	UFUNCTION(Category = Grid, BlueprintCallable)
    TArray<class ADropPointTile*> GetTileORange(const FDropPointGridCoord& Origin, const int32& Range) const;
	
	/**
	* Returns an array of tiles around the origin coordinates, including the origin tile.
	* @param Origin - The origin coordinates.
	* @param Range - The range to iterate through.
	* @param bIncludeOrigin - Include the origin tile or not.
	*/
	UFUNCTION(Category = Grid, BlueprintCallable)
    TArray<class ADropPointTile*> GetTileRange(const FDropPointGridCoord& Origin, const int32& Range, const bool& bIncludeOrigin) const;
	
	/**
	* Returns an array of coordinates around the origin coordinates, excluding the origin coordinate.
	* @param Origin - The origin coordinates.
	* @param Range - The range to iterate through.
	*/
	UFUNCTION(Category = Grid, BlueprintCallable)
    TArray<FDropPointGridCoord> GetCoordORange(const FDropPointGridCoord& Origin, const int32& Range) const;
	
	/**
	* Returns an array of coordinates around the origin coordinates.
	* @param Origin - The origin coordinates.
	* @param Range - The range to iterate through.
	* @param bIncludeOrigin - Include the origin tile or not.
	*/
	UFUNCTION(Category = Grid, BlueprintCallable)
    TArray<FDropPointGridCoord> GetCoordRange(const FDropPointGridCoord& Origin, const int32& Range, const bool& bIncludeOrigin) const;
	
	/**
	 * Sets a referenced unit at the given coordinates. Takes the unit's layer into account. Returns true if successful.
	 * @param Coord - The X and Y values of the desired Coordinate.
	 * @param Unit - The referenced unit to move.
	 * @param bForce - Will replace existing units if set to true.
	 */
	UFUNCTION(Category = Grid, BlueprintCallable)
	bool SetTileUnit(const FDropPointGridCoord& Coord, class ADropPointUnit* Unit, bool bForce) const;

	/**
	 * Checks to see if the tile at the given coordinate has a unit at the given layer.
	 * @param Coord - The X and Y values of the desired Coordinate.
	 * @param Layer - The unit layer to check.
	 */
	UFUNCTION(Category = Grid, BlueprintCallable)
	bool TileHasUnit(const FDropPointGridCoord& Coord, const EUnitLayers& Layer) const;

	/**
	 * Checks to see if the given coordinates are within the current arena bounds.
	 * @param Coord - The X and Y values of the desired Coordinate.
	 */
	UFUNCTION(Category = Grid, BlueprintCallable)
	bool IsInsideArena(const FDropPointGridCoord& Coord) const;

	FORCEINLINE UFUNCTION(Category = DropPoint, BlueprintGetter)
	const TArray<ADropPointUnit*>& GetUnits() const { return Units; };

	/**
	 * Creates a unit and places it into the arena. Returns the new unit if successful.
	 * @param Coord - The X and Y values of the desired Coordinate.
	 * @param UnitType - The type of unit to spawn. Should be a defined BP subclass.
	 * @param Faction - The desired faction to give the new unit.
	 * @param bForce - Whether to replace any existing units at the given coordinates. Takes layering into account.
	 */
	UFUNCTION(Category = DropPoint, BlueprintCallable)
	class ADropPointUnit* CreateUnit(const FDropPointGridCoord& Coord, TSubclassOf<ADropPointUnit>& UnitType, EUnitFactions& Faction, const bool bForce);

	/**
	 * Creates a tile and places it into the arena. Returns the new tile if successful.
	 * @param Coord - The X and Y values of the desired Coordinate.
	 * @param TileType - The type of tile to spawn. Should be a defined BP subclass.
	 * @param bForce - Whether to force replace any existing tile at the given coordinates. If false, will take tile priority into account and might still replace any existing tiles.
	 */
	UFUNCTION(Category = DropPoint, BlueprintCallable)
	class ADropPointTile* CreateTile(const FDropPointGridCoord& Coord, const TSubclassOf<ADropPointTile>& TileType, const bool bForce);

	/**
	 * Ends the current turn, calling all functionality that occurs between turns.
	 */
	UFUNCTION(Category = DropPoint, BlueprintCallable)
	virtual void EndTurn();

	/**
	 * Ends the current turn, calling all functionality that occurs between turns.
	 */
	UFUNCTION(Category = DropPoint, BlueprintCallable)
	TSubclassOf<class ADropPointTile> PickTileFromPool(const float& DistToCenter);

	/**
	 * Spawns the arena.
	 */
	UFUNCTION(Category = DropPoint, BlueprintCallable)
	virtual void SpawnArena();
};



