// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "DropPointBlock.h"
#include "DropPointBlockGrid.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"

ADropPointBlock::ADropPointBlock()
{
	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> TileMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> BaseMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> InactiveMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> ActiveMaterial;
		FConstructorStatics()
			: TileMesh(TEXT("/Engine/BasicShapes/Cube.Cube"))
			, BaseMaterial(TEXT("/Game/Puzzle/Meshes/BaseMaterial.BaseMaterial"))
			, InactiveMaterial(TEXT("/Game/Materials/Dev_Dark_Blue.Dev_Dark_Blue"))
			, ActiveMaterial(TEXT("/Game/Materials/Dev_Base_Blue.Dev_Base_Blue"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->SetStaticMesh(ConstructorStatics.TileMesh.Get());
	BlockMesh->SetRelativeScale3D(FVector(1.f,1.f,0.25f));
	BlockMesh->SetRelativeLocation(FVector(0.f,0.f,25.f));
	BlockMesh->SetMaterial(0, ConstructorStatics.InactiveMaterial.Get());
	BlockMesh->SetupAttachment(DummyRoot);
	BlockMesh->OnClicked.AddDynamic(this, &ADropPointBlock::BlockClicked);
	BlockMesh->OnInputTouchBegin.AddDynamic(this, &ADropPointBlock::OnFingerPressedBlock);

	// Save a pointer to the orange material
	BaseMaterial = ConstructorStatics.BaseMaterial.Get();
	InactiveMaterial = ConstructorStatics.InactiveMaterial.Get();
	ActiveMaterial = ConstructorStatics.ActiveMaterial.Get();
}

void ADropPointBlock::BlockClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	HandleClicked();
}


void ADropPointBlock::OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	HandleClicked();
}

void ADropPointBlock::HandleClicked()
{
	// Check we are not already active
	if (!bIsActive)
	{
		bIsActive = true;

		//// Change material
		//BlockMesh->SetMaterial(0, BlueMaterial);

		//// Tell the Grid
		//if (OwningGrid != nullptr)
		//{
		//	OwningGrid->AddScore();
		//}
	}
}

void ADropPointBlock::Highlight(bool bOn)
{
	// Do not highlight if the block has already been activated.
	if (bIsActive)
	{
		return;
	}

	if (bOn)
	{
		BlockMesh->SetMaterial(0, ActiveMaterial);
	}
	else
	{
		BlockMesh->SetMaterial(0, InactiveMaterial);
	}
}
