// Copyright Daniel Thompson https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#include "DropPointTile.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"

ADropPointTile::ADropPointTile()
{
	struct ConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> TileMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> BaseMaterial;
		ConstructorStatics()
			: TileMesh(TEXT("/Engine/BasicShapes/Cube.Cube"))
			, BaseMaterial(TEXT("/Game/Materials/Dev_Dark_Blue.Dev_Dark_Blue"))
		{
		}
	};

	static ConstructorStatics TileStatics;

	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileMesh0"));
	TileMesh->SetStaticMesh(TileStatics.TileMesh.Get());
	TileMesh->SetMaterial(0, TileStatics.BaseMaterial.Get());
	RootComponent = TileMesh;

	// Save a pointer to the base material
	BaseMaterial = TileStatics.BaseMaterial.Get();
}

// Called when the game starts or when spawned
void ADropPointTile::BeginPlay()
{
	Super::BeginPlay();
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

