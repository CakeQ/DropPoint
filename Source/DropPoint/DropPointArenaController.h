// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#pragma once

#include "DropPointArenaController.generated.h"

UCLASS()
class DROPPOINT_API ADropPointArenaController : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly)
	class USceneComponent* DummyRoot;

public:	
	ADropPointArenaController();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
