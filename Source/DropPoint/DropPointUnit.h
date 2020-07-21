// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DropPointEnums.h"
#include "DropPointGridCoord.h"
#include "DropPointUnit.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateHealthDelegate, const int32&, NewVal);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGatherMineralsDelegate, const int32&, Amount);

/**
 * The base unit type used within the DropPoint game mode. Handles all functionality for units, including calling their abilities.
 * All units within the game should be a blueprint subtype, as the abilities and properties are inherited from the class defaults.
 */
UCLASS()
class DROPPOINT_API ADropPointUnit : public AActor
{
	GENERATED_BODY()
	
public:	
	ADropPointUnit();

protected:
	/** Name of the unit. Used by UI. */
	UPROPERTY(Category = Unit, EditAnywhere, BlueprintReadWrite)
	FString UnitName;

	/** Description of the unit. Used by UI. */
	UPROPERTY(Category = Unit, EditAnywhere, BlueprintReadWrite)
	FString UnitDesc;

	/** Thumbnail of the unit. Used by UI. */
	UPROPERTY(Category = Unit, EditAnywhere, BlueprintReadWrite)
	class UTexture2D* UnitThumbnail;

	/** Unit Mesh. */
	UPROPERTY(Category = References, EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* UnitMesh;

	/** Connected tile within the game grid. Occupies a layer dictated by UnitLayer. */
	UPROPERTY(Category = Unit, VisibleInstanceOnly, BlueprintReadOnly)
	class ADropPointTile* ConnectedTile;

	/** Current unit health. */
	UPROPERTY(Category = Unit, EditAnywhere, BlueprintReadWrite)
	int32 Health = 3;

	/** Maximum possible unit health. */
	UPROPERTY(Category = Unit, EditAnywhere, BlueprintReadWrite)
	int32 MaxHealth = 3;

	/** Time in turns required for this unit to take off when told to do so. */
	UPROPERTY(Category = Unit, EditAnywhere, BlueprintReadWrite)
	int32 TimeToLaunch = 3;

	/** Unit coordinates within the game grid */
	UPROPERTY(Category = Unit, VisibleInstanceOnly, BlueprintReadOnly)
	FDropPointGridCoord UnitCoordinates;

	/** The unit's faction. Dictates if the player can interact with it or if it's hostile/neutral. */
	UPROPERTY(Category = Unit, EditAnywhere, BlueprintReadWrite)
	EUnitFactions UnitFaction = EUnitFactions::Neutral;

	/** The layer which the unit occupies on a tile. */
	UPROPERTY(Category = Unit, EditDefaultsOnly, BlueprintReadWrite)
	EUnitLayers UnitLayer = EUnitLayers::Ground;

	/** Unit properties, stored into a bitmask. See EUnitFlags in DropPointEnums.h for flag descriptions. */
	UPROPERTY(Category = Unit, EditAnywhere, BlueprintReadWrite, meta=(Bitmask, BitmaskEnum = "EUnitFlags"))
	uint8 UnitFlags;

	/** Total amount of minerals stored on this unit. */
	UPROPERTY(Category = Unit, EditAnywhere, BlueprintReadWrite)
	int32 StoredMinerals;

	/** WIP: The core unit this unit is connected to. Should be replaced with the pylon network when possible. */
	class ADropPointUnit* ConnectedCore;

public:
	/** Delegate binding for updating health. */
	UPROPERTY(Category = DropPoint, BlueprintAssignable)
	FUpdateHealthDelegate OnUpdateHealth;

	UPROPERTY(Category = DropPoint, BlueprintAssignable)
	FGatherMineralsDelegate OnGatherMinerals;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	/** Set the unit to start launching. */
	UFUNCTION(Category = Unit, BlueprintCallable)
	void TryLaunch() const;

	/** Trigger all passive abilities the unit has. */
	UFUNCTION(Category = Unit, BlueprintCallable)
	void TriggerAbilities();

	/**
	 * Give the unit minerals to store.
	 * @param Amount - The amount of minerals to give.
	 */
	UFUNCTION(Category = Unit, BlueprintCallable)
	void AddResources(const int32& Amount);

	/**
	 * Adjusts the unit's health value. Will Die() if health drops to zero.
	 * @param Amount - The amount of health to give or take. Can be negative.
	 */
	UFUNCTION(Category = Unit, BlueprintCallable)
	void AdjustHealth(const int32& Amount);

	/** Override base actor TakeDamage. Calls AdjustHealth() with a negative value. */
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	/** WIP: Kills the unit. Should be different from Destroy() as it should leave behind debris. */
	UFUNCTION(Category = Unit, BlueprintCallable)
	void Die();

	/**
	 * Toggles whether or not the unit appears to be highlighted.
	 * @param bOn - The highlight state.
	 */
	UFUNCTION(Category = Unit, BlueprintCallable)
	void HighlightUnit(bool bOn) const;

	/** Triggers any post-create components (such as multi-tiled or scatter replication logic). */
	UFUNCTION(Category = Unit, BlueprintCallable)
	void PostCreateUnit(class ADropPointGameMode* OwnerMode) const;

	/** Gets the unit's current health. */
	FORCEINLINE UFUNCTION(Category = Unit, BlueprintGetter)
	int32 GetHealth() const { return Health; };

	/** Gets the unit's maximum possible health. */
	FORCEINLINE UFUNCTION(Category = Unit, BlueprintGetter)
	const int32& GetMaxHealth() const { return MaxHealth; };

	/** Gets the amount of time in turns left before the unit can launch. */
	FORCEINLINE UFUNCTION(Category = Unit, BlueprintGetter)
	const int32& GetTimeToLaunch() const { return TimeToLaunch; };

	/** Gets the unit's faction. */
	FORCEINLINE UFUNCTION(Category = Unit, BlueprintGetter)
	const EUnitFactions& GetFaction() const { return UnitFaction; };

	/**
	 * Sets the unit's faction.
	 * @param Faction - The faction to set the unit to. See EUnitFactions in DropPointEnums.h for the list of possible factions.
	 */
	FORCEINLINE UFUNCTION(Category = Unit, BlueprintSetter)
	void SetFaction(EUnitFactions& Faction) { UnitFaction = Faction; };

	/** Gets the unit's layer on the grid tile. */
	FORCEINLINE UFUNCTION(Category = Unit, BlueprintGetter)
	const EUnitLayers& GetLayer() const { return UnitLayer; };

	/**
	 * Sets the unit's layer.
	 * @param Layer - The layer to set the unit to. See EUnitLayers in DropPointEnums.h for the list of possible layers.
	 */
	FORCEINLINE UFUNCTION(Category = Unit, BlueprintGetter)
	void SetLayer(EUnitLayers& Layer) { UnitLayer = Layer; };

	/**
	 * WIP: Sets the unit's connected core unit. Should use pylon network when possible.
	 * @param NewCore - The new core unit to use.
	 */
	FORCEINLINE UFUNCTION(Category = Unit, BlueprintGetter)
	void SetCore(ADropPointUnit* NewCore) { ConnectedCore = NewCore; };

	/** Gets the unit's current grid tile. */
	FORCEINLINE UFUNCTION(Category = Unit, BlueprintGetter)
	class ADropPointTile* GetConnectedTile() const { return ConnectedTile; };

	/**
	 * Sets the unit's current grid tile.
	 * @param Tile - The new tile to occupy.
	 */
	FORCEINLINE UFUNCTION(Category = Unit, BlueprintSetter)
	void SetConnectedTile(class ADropPointTile* Tile) {	ConnectedTile = Tile; };

	/**
	 * Sets the unit to have the given coordinates within the grid.
	 * @param NewCoord - The coordinates to use.
	 */
	UFUNCTION(Category = Tile, BlueprintSetter)
	virtual void SetUnitCoords(const FDropPointGridCoord& NewCoord);

	/** Gets the unit's UI name. */
	FORCEINLINE UFUNCTION(Category = Unit, BlueprintGetter)
	const FString& GetUnitName() const { return UnitName; };

	/** Gets the unit's UI description. */
	FORCEINLINE UFUNCTION(Category = Unit, BlueprintGetter)
	const FString& GetUnitDescription() const { return UnitDesc; };

	/** Gets the unit's UI thumbnail. */
	FORCEINLINE UFUNCTION(Category = Unit, BlueprintGetter)
	class UTexture2D* GetUnitThumbnail() const { return UnitThumbnail; };

	/**
	 * Checks to see if the unit has the input property flag.
	 * @param Value - The flag to check.
	 */
	FORCEINLINE UFUNCTION(Category = Unit, BlueprintCallable)
	bool HasUnitFlag(EUnitFlags Value) const { return UnitFlags & (uint8)Value; };

	/** Change the unit's material. */
	FORCEINLINE UFUNCTION(Category = Unit, BlueprintCallable)
	void ChangeMaterial(UMaterialInstance* NewMaterial) const { UnitMesh->SetMaterial(0, NewMaterial); };

	/**
	 * Check to see which two units' factions predicates one another within the enum define. Used to sort units in the game's unit turn order.
	 * @param u1 - The first unit to compare.
	 * @param u2 - The second unit to compare.
	 */
	FORCEINLINE static bool FactionPredicate(const ADropPointUnit& u1, const ADropPointUnit& u2) { return (u1.UnitFaction > u2.UnitFaction); };
};
