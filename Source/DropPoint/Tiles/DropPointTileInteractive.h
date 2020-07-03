// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Tiles/DropPointTile.h"
#include "DropPointTileInteractive.generated.h"

/**
 * Interactive tile used within the DropPoint game mode. Features interactive elements for selection, which the parent tile does not have. All tiles within the arena should be interactive.
 */
UCLASS()
class DROPPOINT_API ADropPointTileInteractive : public ADropPointTile
{
	GENERATED_BODY()
	
public:
	/** Override to set up input binding. */
	ADropPointTileInteractive();

	/** Handle the tile being clicked. */
	UFUNCTION(Category = DropPoint, BlueprintCallable)
	void TileClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	/** Handle the tile being touched. */
	UFUNCTION(Category = DropPoint, BlueprintCallable)
	void TilePressed(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);

	/** Toggle the selection state of the tile. */
	UFUNCTION(Category = DropPoint, BlueprintCallable)
	void ToggleTile();

	/** Activate the tile to be selected. */
	UFUNCTION(Category = DropPoint, BlueprintCallable)
	void ActivateTile();

	/** Deactivate the tile to be unselected. */
	UFUNCTION(Category = DropPoint, BlueprintCallable)
	void DeactivateTile();

	/**
	 * Handles highlighting of the tile.
	 * @param bOn - Whether or not it should be highlighted.
	 */
	UFUNCTION(Category = DropPoint, BlueprintCallable)
	void HighlightTile(bool bOn);
};
