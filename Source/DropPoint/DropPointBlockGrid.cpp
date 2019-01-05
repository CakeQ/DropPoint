// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "DropPointBlockGrid.h"
#include "DropPointBlock.h"
#include "Components/TextRenderComponent.h"
#include "Engine/World.h"

#define LOCTEXT_NAMESPACE "PuzzleBlockGrid"

ADropPointBlockGrid::ADropPointBlockGrid()
{
	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Set defaults
	Size = 7;
	BlockSpacing = 100.f;
}


void ADropPointBlockGrid::BeginPlay()
{
	Super::BeginPlay();

	// Number of blocks
	const int32 NumBlocks = Size * Size;

	// Calculate grid offset

	const int32 GridOffset = floor(((Size * BlockSpacing) / 2)/100) * 100;

	// Loop to spawn each block
	for(int32 BlockIndex=0; BlockIndex<NumBlocks; BlockIndex++)
	{
		const float XOffset = ((BlockIndex/Size) * BlockSpacing) - GridOffset; // Divide by dimension
		const float YOffset = ((BlockIndex%Size) * BlockSpacing) - GridOffset; // Modulo gives remainder

		// Make position vector, offset from Grid location
		const FVector BlockLocation = FVector(XOffset, YOffset, 0.f) + GetActorLocation();

		// Spawn a block
		ADropPointBlock* NewBlock = GetWorld()->SpawnActor<ADropPointBlock>(BlockLocation, FRotator(0,0,0));

		// Tell the block about its owner
		if (NewBlock != nullptr)
		{
			NewBlock->OwningGrid = this;
		}
	}
}

#undef LOCTEXT_NAMESPACE
