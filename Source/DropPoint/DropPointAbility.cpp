// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.


#include "DropPointAbility.h"
#include "DropPointUnit.h"

// Sets default values for this component's properties
UDropPointAbility::UDropPointAbility()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

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

void UDropPointAbility::Trigger(ADropPointUnit* Owner)
{

}

void UDropPointAbility::QueueTrigger(ADropPointUnit* Owner)
{

}

void UDropPointAbility::HandleQueuedTriggers()
{
}

void UDropPointAbility::TickCooldown()
{

}

