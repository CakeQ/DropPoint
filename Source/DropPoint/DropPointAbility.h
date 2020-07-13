// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DropPointEnums.h"
#include "Components/ActorComponent.h"
#include "DropPointAbility.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DROPPOINT_API UDropPointAbility : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDropPointAbility();

protected:
	virtual void BeginPlay() override;

	/** Name of the unit. ability by UI. */
	UPROPERTY(Category = Unit, EditDefaultsOnly, BlueprintReadWrite)
	FString AbilityName;

	/** Description of the ability. Used by UI. */
	UPROPERTY(Category = Unit, EditDefaultsOnly, BlueprintReadWrite)
	FString AbilityDesc;

	/** Thumbnail of the ability. Used by UI. */
	UPROPERTY(Category = Unit, EditDefaultsOnly, BlueprintReadWrite)
	class UTexture2D* AbilityThumbnail;

	/** How the ability handles active calls (instantly, delayed..) */
	UPROPERTY(Category = Unit, EditDefaultsOnly, BlueprintReadWrite)
	EAbilityTypes AbilityType = EAbilityTypes::Instant;

	/** How the ability is categorized and sorted in the UI (standard, biome..) */
	UPROPERTY(Category = Unit, EditDefaultsOnly, BlueprintReadWrite)
	EAbilityCats AbilityCategory = EAbilityCats::Standard;

	/** The cooldown amount used between ability uses. */
	UPROPERTY(Category = Ability, EditAnywhere, BlueprintReadWrite)
	int32 AbilityCooldown = 3;

	/** The amount of turns left before the ability can be used again. */
	UPROPERTY(Category = Ability, EditAnywhere, BlueprintReadWrite)
	int32 AbilityCooldownLeft = 0;

	/** The cooldown amount used between ability uses. */
	UPROPERTY(Category = Ability, EditAnywhere, BlueprintReadWrite)
	int32 AbilityWindup = 3;

	/** The amount of turns left before the ability can be used again. */
	UPROPERTY(Category = Ability, EditAnywhere, BlueprintReadWrite)
	int32 AbilityWindupLeft = 0;

	/** Units awaiting trigger. */
	UPROPERTY(Category = References, VisibleInstanceOnly, BlueprintReadWrite)
	TArray<class ADropPointUnit*> QueuedUnits;

public:
	/** Set the ability type. See EAbilityTypes in DropPointEnums.h for descriptions. */
	FORCEINLINE UFUNCTION(Category = Ability, BlueprintSetter)
	virtual void SetAbilityType(EAbilityTypes NewType) { AbilityType = NewType; };

	/** Set the ability category. See EAbilityCats in DropPointEnums.h for descriptions. */
	FORCEINLINE UFUNCTION(Category = Ability, BlueprintSetter)
	virtual void SetAbilityCategory(EAbilityCats NewCat) { AbilityCategory = NewCat; };

	/** Get the ability type. See EAbilityTypes in DropPointEnums.h for descriptions. */
	FORCEINLINE UFUNCTION(Category = Ability, BlueprintGetter)
	EAbilityTypes GetAbilityType() { return AbilityType; };

	/** Get the ability category. See EAbilityCats in DropPointEnums.h for descriptions. */
	FORCEINLINE UFUNCTION(Category = Ability, BlueprintGetter)
	EAbilityCats GetAbilityCategory() { return AbilityCategory; };

	/** Gets the unit's UI name. */
	FORCEINLINE UFUNCTION(Category = Unit, BlueprintGetter)
	const FString& GetName() { return AbilityName; };

	/** Gets the unit's UI description. */
	FORCEINLINE UFUNCTION(Category = Unit, BlueprintGetter)
	const FString& GetDescription() { return AbilityDesc; };

	/** Gets the unit's UI thumbnail. */
	FORCEINLINE UFUNCTION(Category = Ability, BlueprintGetter)
	class UTexture2D* GetThumbnail() { return AbilityThumbnail; };

	/**
	 * Called when the ability component is selected to fire.
	 * @param Owner - The unit to handle functionality with.
	 */
	UFUNCTION(Category = Ability, BlueprintCallable)
	virtual void Trigger(class ADropPointUnit* Owner);

	/**
	 * Queue the ability to start counting down.
	 * @param Owner - The unit to queue functionality for.
	 */
	UFUNCTION(Category = Ability, BlueprintCallable)
	virtual void QueueTrigger(class ADropPointUnit* Owner);

	/** Tick down the queued windup, and call Trigger when ready. */
	UFUNCTION(Category = Ability, BlueprintCallable)
	virtual void HandleQueuedTriggers();

	/** Tick down the cooldown. */
	UFUNCTION(Category = Ability, BlueprintCallable)
	virtual void TickCooldown();

	/** Returns whether or not the ability is ready to trigger after cooldown. */
	FORCEINLINE UFUNCTION(Category = Ability, BlueprintCallable)
	bool ReadyToTrigger() { return AbilityCooldownLeft <= 0 && AbilityWindupLeft <= 0; };

	/** See if there are any queued triggers awaiting call. */
	FORCEINLINE UFUNCTION(Category = Ability, BlueprintCallable)
	bool HasQueuedTriggers() { return QueuedUnits.Num() > 0; };

	/** Returns how many more turns the ability will be on cooldown. */
	FORCEINLINE UFUNCTION(Category = Ability, BlueprintGetter)
	int32 CheckCooldown() { return AbilityCooldownLeft; };
};
