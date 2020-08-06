// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DropPointUnitItem.h"
#include "GameFramework/Character.h"
#include "DropPointCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPlaceUnitDelegate, TSubclassOf<class ADropPointUnit>, CompareType, const int32&, Amount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPurchaseDelegate, const int32&, Cost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTileDelegate, class ADropPointTile*, Tile);

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

	/** Widget used to display the unit and its abilities. */
	UPROPERTY(Category = Classes, EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UUserWidget> UnitMenuWidgetClass;

	/** Widget used to display the player inventory. */
	UPROPERTY(Category = Classes, EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UUserWidget> UnitInventoryWidgetClass;

	/** Widget used to display the resource tracker. */
	UPROPERTY(Category = Classes, EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UUserWidget> ResourcesWidgetClass;

	/** The player's unit inventory. */
	UPROPERTY(Category = Classes, EditAnywhere, BlueprintReadWrite)
	TArray<FDropPointUnitItem> UnitInventory;

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

	/** Reference to the unit menu widget. */
	UPROPERTY(Category = References, VisibleInstanceOnly, BlueprintReadOnly)
	class UDropPointWidgetUnit* UnitMenuWidget;

	/** Reference to the inventory spawning menu widget. */
	UPROPERTY(Category = References, VisibleInstanceOnly, BlueprintReadOnly)
	class UDropPointWidgetInventory* UnitInventoryWidget;

	/** Reference to the resource tracker widget. */
	UPROPERTY(Category = References, VisibleInstanceOnly, BlueprintReadOnly)
	class UDropPointWidgetResources* ResourcesWidget;

	/** Spring arm for the camera. */
	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadWrite)
	class USpringArmComponent* PawnSpringArm;

	/** The player camera. */
	UPROPERTY(Category = Components, VisibleAnywhere, BlueprintReadWrite)
	class UCameraComponent* PawnCamera;

	/** The material parameter instance used for storing coordinate data for the game's master material. Handles selected and highlighted tile positions as well as configuration for intensity and visibility. */
	UPROPERTY(Category = Material, VisibleAnywhere, BlueprintReadWrite)
	class UMaterialParameterCollectionInstance* HighlightParameters;

	/** The player's faction. */
	UPROPERTY(Category = DropPoint, EditAnywhere, BlueprintReadWrite)
	EUnitFactions PlayerFaction = EUnitFactions::Player;
	
	/** Player properties, stored into a bitmask. See EPlayerFlags in DropPointEnums.h for flag descriptions. */
	UPROPERTY(Category = DropPoint, EditAnywhere, BlueprintReadWrite, meta=(Bitmask, BitmaskEnum = "EPlayerFlags"))
	uint8 PlayerFlags;

	/** The starting expenditures for the player. */
	UPROPERTY(Category = DropPoint, EditAnywhere, BlueprintReadWrite)
	int32 StartingExpenditure = 620;

	/** The amount of minerals the player can spend on units. */
	UPROPERTY(Category = DropPoint, EditAnywhere, BlueprintReadWrite)
	int32 MineralsAvailable = 2000;

public:
	/** Delegate binding for unit placement. */
	UPROPERTY(Category = DropPoint, BlueprintAssignable)
	FPlaceUnitDelegate OnUnitPlaced;

	/** Delegate binding for purchasing units. */
	UPROPERTY(Category = DropPoint, BlueprintAssignable)
	FPurchaseDelegate OnPurchaseUnit;

	/** Delegate binding for selecting tiles. */
	UPROPERTY(Category = DropPoint, BlueprintAssignable)
	FTileDelegate OnTileSelect;
	
protected:
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
	FORCEINLINE UFUNCTION(Category = DropPoint, BlueprintGetter)
	TSubclassOf<class ADropPointUnit> GetUnitSpawnType() const { return UnitSpawnTypeClass; };

	/** Sets the current unit spawn type class. */
	UFUNCTION(Category = DropPoint, BlueprintSetter)
	void SetUnitSpawnType(TSubclassOf<class ADropPointUnit> NewType);

	/** Gets the current amount of minerals the player has access to. */
	FORCEINLINE UFUNCTION(Category = DropPoint, BlueprintGetter)
	const int32& GetMineralBudget() const { return MineralsAvailable; };

	FORCEINLINE UFUNCTION(Category = DropPoint, BlueprintGetter)
	const EUnitFactions& GetFaction() const { return PlayerFaction; };
	
	/**
	* Gives the player a unit to take ownership of. Mostly for connecting up widgets correctly.
	* @param NewUnit - The unit to take ownership of.
	*/
	void AddUnit(class ADropPointUnit* NewUnit) const;
	
	/**
	* Set the player to have only the input flag.
	* @param Value - The input flag to set.
	*/
	UFUNCTION(Category = Tile, BlueprintCallable)
    void SetPlayerFlag(const EPlayerFlags& Value);

	/**
	* Adds the input flag to the player's flags.
	* @param Value - The input flag to add.
	*/
	UFUNCTION(Category = Tile, BlueprintCallable)
    void AddPlayerFlag(const EPlayerFlags& Value);

	/**
	* Removes the input flag from the player's flags.
	* @param Value - The input flag to remove.
	*/
	UFUNCTION(Category = Tile, BlueprintCallable)
    void RemovePlayerFlag(const EPlayerFlags& Value);

	/**
	* Checks to see if the player has the input property flag.
	* @param Value - The flag to check.
	*/
	UFUNCTION(Category = Unit, BlueprintCallable)
    bool HasPlayerFlag(const EPlayerFlags& Value) const;

};
