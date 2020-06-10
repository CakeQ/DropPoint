// Copyright Daniel Thompson https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "DropPointGridCoord.generated.h"

USTRUCT(BlueprintType)
struct DROPPOINT_API FDropPointGridCoord
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DropPoint)
		int32 x;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DropPoint)
		int32 y;	
};
