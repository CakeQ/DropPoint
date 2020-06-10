// Copyright Daniel Thompson https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#include "DropPointTile.h"
#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInstance.h"

ADropPointTile::ADropPointTile()
{
	//struct ConstructorStatics
	//{
	//	ConstructorHelpers::FObjectFinderOptional<UStaticMesh> TileMesh;
	//	ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> BaseMaterial;
	//	ConstructorStatics()
	//		: TileMesh(TEXT("/Engine/BasicShapes/Cube.Cube"))
	//		, BaseMaterial(TEXT("/Game/Materials/Dev_Dark_Blue.Dev_Dark_Blue"))
	//	{
	//	}
	//};

	//static ConstructorStatics TileStatics;

	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileMesh0"));
	RootComponent = TileMesh;

	// Save a pointer to the base material
	//BaseMaterial = TileStatics.BaseMaterial.Get();
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

