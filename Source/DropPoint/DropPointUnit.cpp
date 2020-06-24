// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.


#include "DropPointUnit.h"
#include "DropPointAbility.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstance.h"

// Sets default values
ADropPointUnit::ADropPointUnit()
{
	UnitMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileMesh0"));
	RootComponent = UnitMesh;
}

// Called when the game starts or when spawned
void ADropPointUnit::BeginPlay()
{
	Super::BeginPlay();
	UnitMesh->SetStaticMesh(BaseMesh);
	UnitMesh->SetMaterial(0, BaseMaterial);

	if (AbilityClasses.Num())
	{
		for (TSubclassOf<UDropPointAbility> NewAbilityClass : AbilityClasses)
		{
			UDropPointAbility* NewAbility = NewObject<UDropPointAbility>(this, NewAbilityClass);
			Abilities.Add(NewAbility);
		}
	}
}

// Called every frame
void ADropPointUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADropPointUnit::TryLaunch()
{
	if (GetTimeToLaunch() > 0)
	{
		return;
	}

	//Die();
}

void ADropPointUnit::TriggerAbilities()
{
	for (UDropPointAbility* Ability : Abilities)
	{
		Ability->HandleQueuedTriggers();
		if (Ability->GetAbilityType() == EAbilityTypes::Passive && Ability->ReadyToTrigger())
		{
			Ability->QueueTrigger(this);
		}
	}
}