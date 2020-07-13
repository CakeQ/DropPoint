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
	TArray<UDropPointAbility*> Abilities;
	GetComponents<UDropPointAbility>(Abilities);
	for (UDropPointAbility* Ability : Abilities)
	{
		Ability->HandleQueuedTriggers();
		if (Ability->GetAbilityType() == EAbilityTypes::Passive && Ability->ReadyToTrigger())
		{
			Ability->QueueTrigger(this);
		}
		Ability->TickCooldown();
	}
}

void ADropPointUnit::AddResources(const int32& Amount)
{
	if (ConnectedCore)
	{
		ConnectedCore->AddResources(Amount);
		return;
	}
	StoredMinerals += Amount;
	OnGatherMinerals.Broadcast(Amount);
}

void ADropPointUnit::AdjustHealth(const int32& Amount)
{
	Health = FMath::Clamp(Health + Amount, 0, MaxHealth);
	OnUpdateHealth.Broadcast(Health);
	if (Health <= 0)
	{
		Die();
	}
}

float ADropPointUnit::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	AdjustHealth(-DamageAmount);
	return DamageAmount;
}

void ADropPointUnit::Die()
{
	Destroy();
}

void ADropPointUnit::HighlightUnit(bool bOn)
{
	UnitMesh->SetScalarParameterValueOnMaterials(TEXT("Highlighted"), (float)bOn);
}
