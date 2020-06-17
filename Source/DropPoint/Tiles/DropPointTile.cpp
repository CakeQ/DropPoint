// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#include "DropPointTile.h"
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

void ADropPointTile::setCoords(const int32& xInput, const int32& yInput)
{
	TileCoordinates.x = xInput;
	TileCoordinates.y = yInput;
}

// Called every frame
void ADropPointTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

