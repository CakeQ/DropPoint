// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2019  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/GameModeBase.h"
#include "DropPointGridCoord.h"
#include "DropPointGameMode.generated.h"

UCLASS(minimalapi)
class ADropPointGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADropPointGameMode();

	UPROPERTY(Category = DropPoint, EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> PlayerClass;

	UPROPERTY(Category = DropPoint, BlueprintReadOnly)
	class ADropPointCharacter* PlayerCharacter;

	UPROPERTY(Category = DropPoint, EditAnywhere, BlueprintReadOnly)
	int32 TurnCount = 0;

	UPROPERTY(Category = DropPoint, EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UUserWidget> TurnCountWidgetClass;

	UPROPERTY(Category = DropPoint, BlueprintReadOnly)
	class UDropPointWidgetTurn* TurnCountWidget;

	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
	int32 GridSize = 7;

	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
	float TileSize = 100.0f;

	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
	TArray<class ADropPointTile*> Tiles;

	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> TileTypeClass;

	UFUNCTION(Category = GridBase, BlueprintCallable)
	int32 GetLinearIndex(const FDropPointGridCoord& coord) const;

	UFUNCTION(Category = GridBase, BlueprintCallable)
	int32 IsInLinearRange(const int32& linearIndex, const int32& size) const;

	UFUNCTION(Category = GridBase, BlueprintCallable)
	void SetTilePos(const FDropPointGridCoord& coord, class ADropPointTileInteractive* tile);

	UFUNCTION(Category = GridBase, BlueprintCallable)
	class ADropPointTile* GetTileAtPos(const FDropPointGridCoord& coord) const;

	UFUNCTION(Category = GridBase, BlueprintCallable)
	class ADropPointTile* GetTileStep(const FDropPointGridCoord& origin, const FDropPointGridCoord& offset) const;

	void SetTileUnit(const FDropPointGridCoord& coord, class AActor* NewUnit, bool Force);

	UFUNCTION(Category = Grid, BlueprintCallable)
	bool TileHasUnit(const FDropPointGridCoord& coord) const;

	UFUNCTION(Category = GridBase, BlueprintCallable)
	bool IsInsideArena(const FDropPointGridCoord& coord) const;

	UFUNCTION(Category = GridBase, BlueprintCallable)
	virtual void EndTurn();

	UFUNCTION(Category = GridBase, BlueprintCallable)
	virtual void SpawnArena();

	virtual void BeginPlay() override;

	UFUNCTION(Category = DropPoint, BlueprintCallable)
	void CreateUnit(const FDropPointGridCoord& coord, TSubclassOf<AActor> ClassType, bool Force);
};



