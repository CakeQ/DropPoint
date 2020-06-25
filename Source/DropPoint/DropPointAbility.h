// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DropPointAbility.generated.h"

UENUM()
enum class EAbilityTypes
{
	Instant,
	Passive
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DROPPOINT_API UDropPointAbility : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDropPointAbility();

	// How the ability handles active calls (instantly, delayed..)
	EAbilityTypes AbilityType = EAbilityTypes::Instant;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// The cooldown amount used between ability uses
	int32 AbilityCooldown = 3;

	// The amount of turns left before the ability can be used again
	int32 AbilityCooldownLeft = 0;

	// The cooldown amount used between ability uses
	int32 AbilityWindup = 3;

	// The amount of turns left before the ability can be used again
	int32 AbilityWindupLeft = 0;

	// Units awaiting trigger
	TArray<class ADropPointUnit*> QueuedUnits;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void SetAbilityType(EAbilityTypes NewType);

	// Called when the ability component is selected to fire
	virtual void Trigger(class ADropPointUnit* Owner);

	// Called for abilities with delayed triggers
	virtual void QueueTrigger(class ADropPointUnit* Owner);

	// Call all queued triggers
	virtual void HandleQueuedTriggers();

	virtual void TickCooldown();

	FORCEINLINE EAbilityTypes GetAbilityType() { return AbilityType; };

	FORCEINLINE bool ReadyToTrigger() { return AbilityCooldownLeft <= 0 && AbilityWindupLeft <= 0; };

	FORCEINLINE bool HasQueuedTriggers() { return QueuedUnits.Num() > 0; };

	FORCEINLINE int32 CheckCooldown() { return AbilityCooldownLeft; };
};
