// Copyright Daniel Thompson https://www.cakedan.net/ and Archie Whitehead 2019 All Rights Reserved.

#include "DropPointTile.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"

// Sets default values
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
	static ConstructorStatics constructorStatics;

	// Create dummy root scene component
	m_DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = m_DummyRoot;

	// Create static mesh component
	m_TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileMesh0"));
	m_TileMesh->SetStaticMesh(constructorStatics.TileMesh.Get());
	m_TileMesh->SetMaterial(0, constructorStatics.BaseMaterial.Get());
	m_TileMesh->SetupAttachment(m_DummyRoot);
	
	// Save a pointer to the base material
	m_BaseMaterial = constructorStatics.BaseMaterial.Get();
}

// Called when the game starts or when spawned
void ADropPointTile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADropPointTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

