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

	virtual void Tick(float DeltaSeconds) override;

	void TriggerClick();

	void ScrollZoom(float Value);

	void MoveRight(float Value);

	void MoveUp(float Value);

	void EnablePan();

	void DisablePan();

	void PanRight(float Value);

	void PanUp(float Value);

	void NextAction();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	bool PanCamera;

	int32 PanX;

	int32 PanY;

protected:

	void TraceForBlock(const FVector& Start, const FVector& End, bool bDrawDebugHelpers);

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	class ADropPointTileInteractive* CurrentTileFocus;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	class ADropPointTileInteractive* CurrentActiveTile;

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* PawnSpringArm;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* PawnCamera;
};
