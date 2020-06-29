// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DropPointCharacter.generated.h"

UCLASS(config=Game)
class ADropPointCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ADropPointCharacter();

protected:
	bool bPanCamera = false;

	int32 PanX;

	int32 PanY;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	class ADropPointTileInteractive* CurrentTileFocus;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	class ADropPointTileInteractive* CurrentActiveTile;

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* PawnSpringArm;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* PawnCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Material)
	class UMaterialParameterCollection* HighlightParameterCollection;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Material)
	class UMaterialParameterCollectionInstance* HighlightParameters;

	UPROPERTY(Category = DropPoint, EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class ADropPointUnit> UnitSpawnTypeClass;

	void TraceForBlock(const FVector& Start, const FVector& End, bool bDrawDebugHelpers);

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void TriggerClick();

	void ScrollZoom(float Value);

	void MoveRight(float Value);

	void MoveUp(float Value);

	void EnablePan();

	void DisablePan();

	void PanRight(float Value);

	void PanUp(float Value);

	void NextAction();
};
