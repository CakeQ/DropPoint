// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DropPointGridCoord.h"
#include "DropPointArenaController.generated.h"

UCLASS()
class DROPPOINT_API ADropPointArenaController : public AActor
{
	GENERATED_BODY()
	
	/** Dummy root component */
	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

public:	
	// Sets default values for this actor's properties
	ADropPointArenaController();

	UPROPERTY(Category=Grid, EditAnywhere, BlueprintReadOnly)
	int32 GridSize = 7;

	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
	float TileSize = 100.0f;

	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
	TArray<ADropPointTile*> Tiles;

	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> TileTypeClass;

	UFUNCTION(Category = GridBase, BlueprintCallable)
	int32 GetLinearIndex(const FDropPointGridCoord& coord) const;

	UFUNCTION(Category = GridBase, BlueprintCallable)
	int32 IsInLinearRange(const int32& linearIndex, const int32& size) const;

	UFUNCTION(Category = GridBase, BlueprintCallable)
	virtual void SetTilePos(const FDropPointGridCoord& coord, ADropPointTileInteractive* tile);

	UFUNCTION(Category = GridBase, BlueprintCallable)
	ADropPointTile* GetTilePos(const FDropPointGridCoord& coord) const;

	UFUNCTION(Category = GridBase, BlueprintCallable)
	ADropPointTile* GetTileStep(const FDropPointGridCoord & origin, const FDropPointGridCoord & offset) const;

	UFUNCTION(Category = GridBase, BlueprintCallable)
	const bool IsInsideArena(const FDropPointGridCoord & coord) const;

	UFUNCTION(Category = GridBase, BlueprintCallable)
	virtual void EndTurn();

	UFUNCTION(Category = GridBase, BlueprintCallable)
	virtual void SpawnArena();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }

};
