// Copyright Daniel Thompson https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

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
	int32 GridSize;

	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
	int32 TurnCount;

	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
	float TileSize;

	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
	TArray<ADropPointTile*> Tiles;

	UFUNCTION(Category = GridBase, BlueprintCallable)
	int32 getLinearIndex(const FDropPointGridCoord& coord) const;

	UFUNCTION(Category = GridBase, BlueprintCallable)
	int32 isInLinearRange(const int32& linearIndex, const int32& size) const;

	UFUNCTION(Category = GridBase, BlueprintCallable)
	virtual void setTilePos(const FDropPointGridCoord& coord, ADropPointTileInteractive* tile);

	UFUNCTION(Category = GridBase, BlueprintCallable)
	ADropPointTile* getTilePos(const FDropPointGridCoord& coord) const;

	UFUNCTION(Category = GridBase, BlueprintCallable)
	ADropPointTile* getTileStep(const FDropPointGridCoord & origin, const FDropPointGridCoord & offset) const;

	UFUNCTION(Category = GridBase, BlueprintCallable)
	const bool isInsideArena(const FDropPointGridCoord & coord) const;

	UFUNCTION(Category = GridBase, BlueprintCallable)
	virtual void endTurn();

	UFUNCTION(Category = GridBase, BlueprintCallable)
	virtual void spawnArena();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }

};
