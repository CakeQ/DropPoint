// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DropPointEnums.h"
#include "Components/ActorComponent.h"
#include "DropPointAbility.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DROPPOINT_API UDropPointAbility : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDropPointAbility();

	/** How the ability handles active calls (instantly, delayed..) */
	EAbilityTypes AbilityType = EAbilityTypes::Instant;

protected:
	virtual void BeginPlay() override;

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
	UFUNCTION(Category = Ability, BlueprintSetter)
	virtual void SetAbilityType(EAbilityTypes NewType);

	/** Get the ability type. See EAbilityTypes in DropPointEnums.h for descriptions. */
	UFUNCTION(Category = Ability, BlueprintGetter)
	FORCEINLINE EAbilityTypes GetAbilityType() { return AbilityType; };

	/**
	 * Called when the ability component is selected to fire.
	 * @param Owner - The unit to handle functionality with.
	 */
	UFUNCTION(Category = Ability, BlueprintCallable)
	virtual void Trigger(class ADropPointUnit* Owner) = 0;

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
	UFUNCTION(Category = Ability, BlueprintCallable)
	FORCEINLINE bool ReadyToTrigger() { return AbilityCooldownLeft <= 0 && AbilityWindupLeft <= 0; };

	/** See if there are any queued triggers awaiting call. */
	UFUNCTION(Category = Ability, BlueprintCallable)
	FORCEINLINE bool HasQueuedTriggers() { return QueuedUnits.Num() > 0; };

	/** Returns how many more turns the ability will be on cooldown. */
	UFUNCTION(Category = Ability, BlueprintGetter)
	FORCEINLINE int32 CheckCooldown() { return AbilityCooldownLeft; };
};
