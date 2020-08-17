// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#include "DropPointTileInteractive.h"
#include "DropPointUnit.h"
#include "Components/StaticMeshComponent.h"

ADropPointTileInteractive::ADropPointTileInteractive()
{
	
}

void ADropPointTileInteractive::UpdateMaterialVisuals()
{
	Super::UpdateMaterialVisuals();
	GridMesh->SetScalarParameterValueOnMaterials(TEXT("Selected"), HasTileFlag(ETileFlags::Selected));
	GridMesh->SetScalarParameterValueOnMaterials(TEXT("Highlighted"), HasTileFlag(ETileFlags::Highlighted));
	GridMesh->SetScalarParameterValueOnMaterials(TEXT("Targeted"), HasTileFlag(ETileFlags::Targeted));
}

void ADropPointTileInteractive::TileClicked(UPrimitiveComponent * ClickedComp, FKey ButtonClicked)
{
	ActivateTile();
}

void ADropPointTileInteractive::TilePressed(ETouchIndex::Type FingerIndex, UPrimitiveComponent * TouchedComponent)
{
	ActivateTile();
}

void ADropPointTileInteractive::ToggleTile()
{
	if (!HasTileFlag(ETileFlags::Selected))
	{
		ActivateTile();
	}
	else
	{
		DeactivateTile();
	}
}

void ADropPointTileInteractive::ActivateTile()
{
	AddTileFlag(ETileFlags::Selected);
	for (ADropPointUnit* Unit : Units)
	{
		Unit->HighlightUnit(true);
	}
}

void ADropPointTileInteractive::DeactivateTile()
{
	RemoveTileFlag(ETileFlags::Selected);
	if (!HasTileFlag(ETileFlags::Highlighted))
	{
		for (ADropPointUnit* Unit : Units)
		{
			Unit->HighlightUnit(false);
		}
	}
}

void ADropPointTileInteractive::HighlightTile(bool bOn)
{
	if (bOn)
	{
		AddTileFlag(ETileFlags::Highlighted);
	}
	else
	{
		RemoveTileFlag(ETileFlags::Highlighted);
	}

	if (!HasTileFlag(ETileFlags::Selected))
	{
		for (ADropPointUnit* Unit : Units)
		{
			Unit->HighlightUnit(bOn);
		}
	}
}
