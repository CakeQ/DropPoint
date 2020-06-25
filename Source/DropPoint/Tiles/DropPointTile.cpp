// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#include "DropPointTile.h"
#include "DropPointUnit.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstance.h"
#include "UObject/ConstructorHelpers.h"

ADropPointTile::ADropPointTile()
{
	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileMesh0"));
	RootComponent = TileMesh;
}

// Called when the game starts or when spawned
void ADropPointTile::BeginPlay()
{
	Super::BeginPlay();
	TileMesh->SetStaticMesh(BaseMesh);
	TileMesh->SetMaterial(0, BaseMaterial);
}

void ADropPointTile::SetTileCoords(const FDropPointGridCoord& NewCoord)
{
	TileCoordinates = NewCoord;
}

void ADropPointTile::SetUnit(ADropPointUnit* NewUnit, bool bForce = false)
{
	if ((!NewUnit || Unit) && !bForce)
	{
		return;
	}
	Unit = NewUnit;
	Unit->SetConnectedTile(this);
	Unit->SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, 50.0f));
}

// Called every frame
void ADropPointTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADropPointTile::SetTileFlag(const ETileFlags& Value)
{
	TileFlags = Value;
}

void ADropPointTile::AddTileFlag(const ETileFlags& Value)
{
	TileFlags |= Value;
}

void ADropPointTile::RemoveTileFlag(const ETileFlags& Value)
{
	TileFlags &= ~Value;
}

bool ADropPointTile::HasTileFlag(const ETileFlags& Value)
{
	return (uint8)TileFlags & (uint8)Value;
}

