// Copyright Daniel Thompson https://www.cakedan.net/ and Archie Whitehead 2019  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DropPointTile.generated.h"

UCLASS()
class DROPPOINT_API ADropPointTile : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ADropPointTile();

	// Pointer to base material used on default state
	UPROPERTY()
	class UMaterialInstance* m_BaseMaterial;

	// Grid that owns us
	UPROPERTY()
	class ADropPointBlockGrid* m_OwningGrid;

protected:
	// Dummy root component
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* m_DummyRoot;

	// StaticMesh component for the tile
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* m_TileMesh;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//FString m_MeshPath = "/Engine/BasicShapes/Cube.Cube";
	//FString m_BaseMaterialPath = "/Game/Puzzle/Meshes/BaseMaterial.BaseMaterial";

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
