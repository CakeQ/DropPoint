// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2019  All Rights Reserved.

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

protected:

	// StaticMesh component for the tile
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Tile)
	class UStaticMeshComponent* TileMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tile)
	class UStaticMesh* BaseMesh;

	// Pointer to base material used on default state
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tile)
	class UMaterialInstance* BaseMaterial;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Tile)
	FDropPointGridCoord TileCoordinates;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Tile)
	class ADropPointUnit* Unit;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(Category = Tile, BlueprintCallable)
	FORCEINLINE FDropPointGridCoord& GetGridCoords() { return TileCoordinates; };

	UFUNCTION(Category = Tile, BlueprintCallable)
	virtual void SetTileCoords(const FDropPointGridCoord& NewCoord);

	UFUNCTION(Category = Tile, BlueprintCallable)
	FORCEINLINE bool HasUnit() { return Unit != nullptr; };

	UFUNCTION(Category = Tile, BlueprintCallable)
	void SetUnit(class ADropPointUnit* NewUnit, bool Force);

};
