// Copyright Daniel Thompson https://github.com/CakeQ and Archie Whitehead 2019  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DropPoint/DropPointGridCoord.h"
#include "DropPointTile.generated.h"

UCLASS()
class DROPPOINT_API ADropPointTile : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ADropPointTile();

	// Grid that owns us
	UPROPERTY()
	class ADropPointArenaController* m_OwningGrid;

	UFUNCTION(Category = Block, BlueprintCallable)
	FORCEINLINE FDropPointGridCoord& getCoords() { return TileCoordinates; };

	UFUNCTION(Category = Block, BlueprintCallable)
	virtual void setCoords(const int32& xInput, const int32& yInput);

protected:

	// StaticMesh component for the tile
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* TileMesh;

	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FDropPointGridCoord TileCoordinates;

	// Pointer to base material used on default state
	UPROPERTY()
	class UMaterialInstance* BaseMaterial;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//FString m_MeshPath = "/Engine/BasicShapes/Cube.Cube";
	//FString m_BaseMaterialPath = "/Game/Puzzle/Meshes/BaseMaterial.BaseMaterial";

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
