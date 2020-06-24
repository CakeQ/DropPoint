// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.


#include "DropPointAbility.h"
#include "DropPointUnit.h"

// Sets default values for this component's properties
UDropPointAbility::UDropPointAbility()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//if (AbilityTypeIn)
	//{
	//	AbilityType = AbilityTypeIn
	//}
	// ...
}


// Called when the game starts
void UDropPointAbility::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDropPointAbility::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDropPointAbility::SetAbilityType(EAbilityTypes NewType)
{
	AbilityType = NewType;
}

void UDropPointAbility::Trigger(ADropPointUnit* Owner)
{
	// Ability does it's actual action here.
}

// Called by the unit, either on activation (active ability) or on turn end (passive ability).
void UDropPointAbility::QueueTrigger(ADropPointUnit* Owner)
{
	// If the ability has no windup, trigger it immediately.
	if (AbilityWindup <= 0)
	{
		Trigger(Owner);
		return;
	}

	// Otherwise, queue the unit and start the windup.
	QueuedUnits.Add(Owner);
	AbilityWindupLeft = AbilityWindup;
}

// Called by the unit on turn end. Handles both active and passive abilities.
void UDropPointAbility::HandleQueuedTriggers()
{
	AbilityWindupLeft = FMath::Clamp(AbilityWindupLeft - 1, 0, AbilityWindup);
	if (AbilityWindupLeft > 0)
	{
		return;
	}

	for (ADropPointUnit* UnitToTrigger : QueuedUnits)
	{
		Trigger(UnitToTrigger);
	}
}

void UDropPointAbility::TickCooldown()
{
	AbilityCooldownLeft = FMath::Clamp(AbilityCooldownLeft - 1, 0, AbilityCooldown);
}

