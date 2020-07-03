// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DropPointCharacter.generated.h"

/**
 * The character class used by the DropPoint game mode. Handles all interactions with the game grid, units, and UI.
 */
UCLASS(config=Game)
class ADropPointCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ADropPointCharacter();

protected:

	/** The material parameter instance class used for storing coordinate data for the game's master material. Handles selected and highlighted tile positions as well as configuration for intensity and visibility. */
	UPROPERTY(Category = Classes, EditAnywhere, BlueprintReadWrite)
	class UMaterialParameterCollection* HighlightParameterCollection;

	/** The current unit type class that will be spawned. */
	UPROPERTY(Category = Classes, EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class ADropPointUnit> UnitSpawnTypeClass;

	/** Whether or not the player is using the pan camera feature. Disables grid tracing when active. */
	UPROPERTY(Category = Camera, EditInstanceOnly, BlueprintReadWrite)
	bool bPanCamera = false;

	/** The X position of the mouse cursor when the pan camera feature was enabled. Reverts the mouse position to this value when exiting camera pan. */
	UPROPERTY(Category = Camera, EditInstanceOnly, BlueprintReadWrite)
	int32 PanX;

	/** The Y position of the mouse cursor when the pan camera feature was enabled. Reverts the mouse position to this value when exiting camera pan. */
	UPROPERTY(Category = Camera, EditInstanceOnly, BlueprintReadWrite)
	int32 PanY;

	/** The current highlighted tile that the mouse is hovering over. */
	UPROPERTY(Category = References, EditInstanceOnly, BlueprintReadWrite)
	class ADropPointTileInteractive* CurrentTileFocus;

	/** The current selected tile that has been clicked on. */
	UPROPERTY(Category = References, EditInstanceOnly, BlueprintReadWrite)
	class ADropPointTileInteractive* CurrentActiveTile;

	/** Spring arm for the camera. */
	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadWrite)
	class USpringArmComponent* PawnSpringArm;

	/** The player camera. */
	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadWrite)
	class UCameraComponent* PawnCamera;

	/** The material parameter instance used for storing coordinate data for the game's master material. Handles selected and highlighted tile positions as well as configuration for intensity and visibility. */
	UPROPERTY(Category = Material, VisibleAnywhere, BlueprintReadWrite)
	class UMaterialParameterCollectionInstance* HighlightParameters;

	/**
	 * Traces the world space from the camera position based on the mouse cursor to select and highlight tiles and units within the game arena.
	 * @param Start - The starting coordinate to trace from.
	 * @param End - The end coordinate to trace to.
	 * @param bDrawDebugHelpers - Draws a red line between the trace coordinates if true.
	 */
	UFUNCTION(Category = DropPoint, BlueprintCallable)
	void TraceForBlock(const FVector& Start, const FVector& End, bool bDrawDebugHelpers);

public:
	/** Override that sets up the player camera and spring arm. */
	virtual void BeginPlay() override;

	/** Override that handles cursor tracing within the arena. */
	virtual void Tick(float DeltaSeconds) override;

	/** Override that sets up input for the DropPoint game mode. */
	UFUNCTION(Category = DropPoint, BlueprintCallable)
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	/** Handles highlighted and selected tile referencing. */
	UFUNCTION(Category = DropPoint, BlueprintCallable)
	void TriggerClick();

	/** Handles moving the camera in and out for zooming. */
	UFUNCTION(Category = DropPoint, BlueprintCallable)
	void ScrollZoom(float Value);

	/**
	 * Moves the character left and right.
	 * @param Value - The amount to move. Can be negative.
	 */
	UFUNCTION(Category = DropPoint, BlueprintCallable)
	void MoveRight(float Value);

	/**
	 * Moves the character up and down (horizontally).
	 * @param Value - The amount to move. Can be negative.
	 */
	UFUNCTION(Category = DropPoint, BlueprintCallable)
	void MoveUp(float Value);

	/** Enables camera panning */
	UFUNCTION(Category = DropPoint, BlueprintCallable)
	void EnablePan();

	/** Disables camera panning */
	UFUNCTION(Category = DropPoint, BlueprintCallable)
	void DisablePan();

	/**
	 * Moves the character left and right using mouse positioning.
	 * @param Value - The amount to move. Can be negative.
	 */
	UFUNCTION(Category = DropPoint, BlueprintCallable)
	void PanRight(float Value);

	/**
	 * Moves the character up and down (horizontally) using mouse positioning.
	 * @param Value - The amount to move. Can be negative.
	 */
	UFUNCTION(Category = DropPoint, BlueprintCallable)
	void PanUp(float Value);

	/** Moves the game state to the next action. This can mean ending the turn or moving on to the next required input. */
	UFUNCTION(Category = DropPoint, BlueprintCallable)
	void NextAction();

	/** Gets the current unit spawn type class. */
	UFUNCTION(Category = DropPoint, BlueprintGetter)
	FORCEINLINE TSubclassOf<class ADropPointUnit> GetUnitSpawnType() { return UnitSpawnTypeClass; };

	/** Sets the current unit spawn type class. */
	UFUNCTION(Category = DropPoint, BlueprintSetter)
	FORCEINLINE void SetUnitSpawnType(TSubclassOf<class ADropPointUnit> NewType) { UnitSpawnTypeClass = NewType; };
};
