// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2019  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DropPoint/DropPointGridCoord.h"
#include "DropPointTile.generated.h"

UENUM()
enum class ETileFlags : uint8
{
	None,
	Highlighted = 0x01,
	Selected = 0x02,
	IncomingUnit = 0x04,
	IncomingDamage = 0x08,
	HasMinerals = 0x16
};
ENUM_CLASS_FLAGS(ETileFlags)

UCLASS()
class DROPPOINT_API ADropPointTile : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ADropPointTile();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tile)
	ETileFlags TileFlags = ETileFlags::None;

	// StaticMesh component for the tile
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Tile)
	class UStaticMeshComponent* TileMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Tile)
	FDropPointGridCoord TileCoordinates;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Tile)
	class ADropPointUnit* Unit;

public:	

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetTileFlag(const ETileFlags& Value);

	void AddTileFlag(const ETileFlags& Value);

	void RemoveTileFlag(const ETileFlags& Value);

	bool HasTileFlag(const ETileFlags& Value);

	UFUNCTION(Category = Tile, BlueprintCallable)
	FORCEINLINE FDropPointGridCoord& GetGridCoords() { return TileCoordinates; };

	UFUNCTION(Category = Tile, BlueprintCallable)
	virtual void SetTileCoords(const FDropPointGridCoord& NewCoord);

	UFUNCTION(Category = Tile, BlueprintCallable)
	FORCEINLINE bool HasUnit() { return Unit != nullptr; };

	UFUNCTION(Category = Tile, BlueprintCallable)
	void SetUnit(class ADropPointUnit* NewUnit, bool bForce);

};
