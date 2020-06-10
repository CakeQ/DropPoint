// Copyright Daniel Thompson https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#include "DropPointTileInteractive.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"

ADropPointTileInteractive::ADropPointTileInteractive()
{

	struct ConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> HighlightMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> ActiveMaterial;
		ConstructorStatics()
			: HighlightMaterial(TEXT("/Game/Materials/Dev_Base_Blue.Dev_Base_Blue"))
			, ActiveMaterial(TEXT("/Game/Materials/Dev_Stripe_Blue.Dev_Stripe_Blue"))
		{
		}
	};

	static ConstructorStatics TileStatics;

	//m_TileMesh->SetMaterial(0, constructorStatics.ActiveMaterial.Get());
	TileMesh->OnClicked.AddDynamic(this, &ADropPointTileInteractive::TileClicked);
	TileMesh->OnInputTouchBegin.AddDynamic(this, &ADropPointTileInteractive::TilePressed);

	// Save a pointer to the materials
	HighlightMaterial = TileStatics.HighlightMaterial.Get();
	ActiveMaterial = TileStatics.ActiveMaterial.Get();
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
	if (!IsActive)
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
	TileMesh->SetMaterial(0, ActiveMaterial);
	IsActive = true;
}

void ADropPointTileInteractive::DeactivateTile()
{
	TileMesh->SetMaterial(0, BaseMaterial);
	IsActive = false;
}

void ADropPointTileInteractive::HighlightTile(bool bOn)
{
	if (IsActive)
	{
		return;
	}

	if (bOn)
	{
		TileMesh->SetMaterial(0, HighlightMaterial);
	}
	else
	{
		TileMesh->SetMaterial(0, BaseMaterial);
	}
}
