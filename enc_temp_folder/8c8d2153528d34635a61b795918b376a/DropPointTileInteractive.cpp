// Copyright Daniel Thompson https://www.cakedan.net/ and Archie Whitehead 2019 All Rights Reserved.

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
	static ConstructorStatics constructorStatics;
	//m_TileMesh->SetMaterial(0, constructorStatics.ActiveMaterial.Get());
	m_TileMesh->OnClicked.AddDynamic(this, &ADropPointTileInteractive::tileClicked);
	m_TileMesh->OnInputTouchBegin.AddDynamic(this, &ADropPointTileInteractive::tilePressed);

	// Save a pointer to the materials
	m_HighlightMaterial = constructorStatics.HighlightMaterial.Get();
	m_ActiveMaterial = constructorStatics.ActiveMaterial.Get();
}

void ADropPointTileInteractive::tileClicked(UPrimitiveComponent * ClickedComp, FKey ButtonClicked)
{
	activateTile();
}

void ADropPointTileInteractive::tilePressed(ETouchIndex::Type FingerIndex, UPrimitiveComponent * TouchedComponent)
{
	activateTile();
}

void ADropPointTileInteractive::activateTile()
{
	if (!m_IsActive)
	{
		m_TileMesh->SetMaterial(0, m_ActiveMaterial);
	}
	else
	{
		m_TileMesh->SetMaterial(0, m_BaseMaterial);
	}

	m_IsActive = !m_IsActive;
}

void ADropPointTileInteractive::highlightTile(bool bOn)
{
	if (m_IsActive)
	{
		return;
	}

	if (bOn)
	{
		m_TileMesh->SetMaterial(0, m_HighlightMaterial);
	}
	else
	{
		m_TileMesh->SetMaterial(0, m_BaseMaterial);
	}
}
