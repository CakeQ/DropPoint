// Copyright Daniel Thompson https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Tiles/DropPointTile.h"
#include "DropPointTileInteractive.generated.h"

/**
 * 
 */
UCLASS()
class DROPPOINT_API ADropPointTileInteractive : public ADropPointTile
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ADropPointTileInteractive();

	// Are we currently active?
	bool IsActive;

	// Pointer to highlighted material used when highlighted
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tile, meta = (AllowPrivateAccess = "true"))
	class UMaterialInstance* HighlightMaterial;

	// Pointer to active material used when clicked on or activated
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tile, meta = (AllowPrivateAccess = "true"))
	class UMaterialInstance* ActiveMaterial;

	// Handle the tile being clicked
	UFUNCTION()
	void TileClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	// Handle the tile being touched
	UFUNCTION()
	void TilePressed(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);

	// Tile interaction functions
	void ToggleTile();
	void ActivateTile();
	void DeactivateTile();

	void HighlightTile(bool bOn);

protected:
	//FString m_HighlightMaterialPath, m_ActiveMaterialPath;
};
