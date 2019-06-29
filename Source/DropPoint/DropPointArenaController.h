// Copyright Daniel Thompson https://www.cakedan.net/ and Archie Whitehead 2019 All Rights Reserved.

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
	int32 m_GridSize;

	int32 getLinearIndex(const FDropPointGridCoord& coord) const { return (coord.y * m_GridSize) + coord.x; }

	UFUNCTION(Category = GridBase, BlueprintCallable)
	int32 isInLinearRange(const int32& linearIndex, const int32& size) const;

	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
	float m_BlockSpacing;

	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
	TArray<ADropPointTileInteractive*> m_Tiles;

	UFUNCTION(Category = GridBase, BlueprintCallable)
	virtual void setTilePos(const FDropPointGridCoord& coord, ADropPointTileInteractive* tile);

	UFUNCTION(Category = GridBase, BlueprintCallable)
	ADropPointTileInteractive* getTilePos(const FDropPointGridCoord& coord, bool& outOfBounds) const;

	UFUNCTION(Category = GridBase, BlueprintCallable)
	const bool isInsideArena(const FDropPointGridCoord & coord) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }

};
