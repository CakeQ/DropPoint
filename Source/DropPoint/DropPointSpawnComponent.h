// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DropPointGridCoord.h"
#include "Components/ActorComponent.h"
#include "DropPointSpawnComponent.generated.h"

UCLASS()
class DROPPOINT_API UDropPointSpawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDropPointSpawnComponent();

	virtual void Fire(class ADropPointGameMode* OwnerMode, const FDropPointGridCoord& Coordinates);
};
