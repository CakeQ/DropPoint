// Copyright Daniel Thompson https://www.cakedan.net/ and Archie Whitehead 2019 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
	float m_BlockSpacing;

	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
	FVector2D m_ArenaGrid;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }

};
