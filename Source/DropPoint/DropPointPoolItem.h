// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DropPointPoolItem.generated.h"

/**
 * Bonus struct used by FDropPointPoolItem
 */
USTRUCT(BlueprintType)
struct DROPPOINT_API FDropPointPoolBonus
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = Weights, EditInstanceOnly, BlueprintReadOnly)
	float BonusWeight = 0.0;

	UPROPERTY(Category = Weights, EditInstanceOnly, BlueprintReadOnly)
	int32 BonusDistanceMin = -1;

	UPROPERTY(Category = Weights, EditInstanceOnly, BlueprintReadOnly)
	int32 BonusDistanceMax = -1;

	FORCEINLINE UFUNCTION(Category = Weights, EditInstanceOnly, BlueprintReadOnly)
	float GetLocationBonus(const int32& CurrentDistance) const { return (BonusDistanceMin <= CurrentDistance && CurrentDistance <= BonusDistanceMax) ? BonusWeight : 0; };
};

/**
 * A basic struct used by the DropPoint game mode to store a tile type and its possible spawn chances.
 */
USTRUCT(BlueprintType)
struct DROPPOINT_API FDropPointPoolItem
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = Weights, EditInstanceOnly, BlueprintReadOnly)
	float BaseWeight = 1.0;

	UPROPERTY(Category = Weights, EditInstanceOnly, BlueprintReadOnly)
	TArray<FDropPointPoolBonus> BonusWeights;

	UPROPERTY(Category = Classes, EditInstanceOnly, BlueprintReadOnly)
	TSubclassOf<class ADropPointTile> TileClass;

	FORCEINLINE UFUNCTION()
	float GetWeight(const int32& CurrentDistance);
};
