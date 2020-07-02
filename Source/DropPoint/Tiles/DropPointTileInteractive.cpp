// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#include "DropPointTileInteractive.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"

ADropPointTileInteractive::ADropPointTileInteractive()
{
	TileMesh->OnClicked.AddDynamic(this, &ADropPointTileInteractive::TileClicked);
	TileMesh->OnInputTouchBegin.AddDynamic(this, &ADropPointTileInteractive::TilePressed);
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
	TileMesh->SetScalarParameterValueOnMaterials(TEXT("Selected"), 1.0f);
}

void ADropPointTileInteractive::DeactivateTile()
{
	RemoveTileFlag(ETileFlags::Selected);
	TileMesh->SetScalarParameterValueOnMaterials(TEXT("Selected"), 0.0f);
}

void ADropPointTileInteractive::HighlightTile(bool bOn)
{
	if (HasTileFlag(ETileFlags::Selected))
	{
		return;
	}

	if (bOn)
	{
		AddTileFlag(ETileFlags::Highlighted);
		TileMesh->SetScalarParameterValueOnMaterials(TEXT("Highlighted"), 1.0f);
	}
	else
	{
		RemoveTileFlag(ETileFlags::Highlighted);
		TileMesh->SetScalarParameterValueOnMaterials(TEXT("Highlighted"), 0.0f);
	}
}
