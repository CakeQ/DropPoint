// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2019  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DropPointEnums.h"
#include "DropPointGridCoord.h"
#include "GameFramework/Actor.h"
#include "GameFramework/GameModeBase.h"
#include "DropPointGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEndTurnDelegate, int32, NewCount);

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

	/** Widget used to display the unit spawning inventory. */
	UPROPERTY(Category = Classes, EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UUserWidget> UnitMenuWidgetClass;

	/** WIP: The current tile class used to populate the map. This will be replaced. */
	UPROPERTY(Category = Classes, EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> TileTypeClass;

	/** The unit class types used to populate the unit spawning inventory. Dictates what the player is allowed to spawn. */
	UPROPERTY(Category = Classes, EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<class ADropPointUnit>> UnitSpawnClasses;

	/** Reference to the player character. */
	UPROPERTY(Category = References, VisibleInstanceOnly, BlueprintReadWrite)
	class ADropPointCharacter* PlayerCharacter;

	/** Reference to the turn tracking widget. */
	UPROPERTY(Category = References, VisibleInstanceOnly, BlueprintReadOnly)
	class UDropPointWidgetTurn* TurnCountWidget;

	/** Reference to the unit spawning menu widget. */
	UPROPERTY(Category = References, VisibleInstanceOnly, BlueprintReadOnly)
	class UDropPointWidgetInventory* UnitMenuWidget;

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

	/** The size (in UE4 units) that each tile within the grid will occupy. */
	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadWrite)
	float TileSize = 100.0f;

public:
	/** Delegate binding for turn ending. */
	UPROPERTY()
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
	int32 IsInLinearRange(const int32& Index, const int32& Size) const;

	/**
	 * Sets a referenced tile at the given coordinates.
	 * @param Coord - The X and Y values of the desired Coordinate.
	 * @param Tile - The referenced tile to move.
	 */
	UFUNCTION(Category = Grid, BlueprintCallable)
	void SetTilePos(const FDropPointGridCoord& Coord, class ADropPointTileInteractive* tile);

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
	 * Sets a referenced unit at the given coordinates. Takes the unit's layer into account.
	 * @param Coord - The X and Y values of the desired Coordinate.
	 * @param Unit - The referenced unit to move.
	 * @param bForce - Will replace existing units if set to true.
	 */
	UFUNCTION(Category = Grid, BlueprintCallable)
	void SetTileUnit(const FDropPointGridCoord& Coord, class ADropPointUnit* Unit, bool bForce);

	/**
	 * Checks to see if the tile at the given coordinate has a unit at the given layer.
	 * @param Coord - The X and Y values of the desired Coordinate.
	 * @param Layer - The unit layer to check.
	 */
	UFUNCTION(Category = Grid, BlueprintCallable)
	bool TileHasUnit(const FDropPointGridCoord& Coord, EUnitLayers layer) const;

	/**
	 * Checks to see if the given coordinates are within the current arena bounds.
	 * @param Coord - The X and Y values of the desired Coordinate.
	 */
	UFUNCTION(Category = Grid, BlueprintCallable)
	bool IsInsideArena(const FDropPointGridCoord& Coord) const;

	/**
	 * Ends the current turn, calling all functionality that occurs between turns.
	 */
	UFUNCTION(Category = DropPoint, BlueprintCallable)
	virtual void EndTurn();

	/**
	 * Spawns the arena.
	 */
	UFUNCTION(Category = DropPoint, BlueprintCallable)
	virtual void SpawnArena();

	/**
	 * Creates a unit and places it into the arena.
	 * @param Coord - The X and Y values of the desired Coordinate.
	 * @param UnitType - The type of unit to spawn. Should be a defined BP subclass.
	 * @param Faction - The desired faction to give the new unit.
	 * @param bForce - Whether to replace any existing units at the given coordinates. Takes layering into account.
	 */
	UFUNCTION(Category = DropPoint, BlueprintCallable)
	void CreateUnit(const FDropPointGridCoord& Coord, TSubclassOf<class ADropPointUnit> UnitType, EUnitFactions Faction, bool bForce);
};



