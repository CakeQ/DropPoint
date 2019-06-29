// Copyright Daniel Thompson https://www.cakedan.net/ and Archie Whitehead 2019 All Rights Reserved.

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
	bool m_IsActive;

	// Pointer to highlighted material used when highlighted
	UPROPERTY()
		class UMaterialInstance* m_HighlightMaterial;

	// Pointer to active material used when clicked on or activated
	UPROPERTY()
		class UMaterialInstance* m_ActiveMaterial;

	// Handle the tile being clicked
	UFUNCTION()
		void tileClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	// Handle the tile being touched
	UFUNCTION()
		void tilePressed(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent);

	// Tile interaction functions
	void activateTile();

	void highlightTile(bool bOn);

protected:
	//FString m_HighlightMaterialPath, m_ActiveMaterialPath;
};
