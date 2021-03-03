// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.


#include "DropPointUnit.h"
#include "DropPointAbility.h"
#include "DropPointGameMode.h"
#include "DropPointSpawnComponent.h"
#include "Components/StaticMeshComponent.h"

ADropPointUnit::ADropPointUnit(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, UnitName(NAME_None)
	, UnitDesc()
	, UnitThumbnail(nullptr)
	, UnitMesh(nullptr)
	, ConnectedTile(nullptr)
	, Health(3)
	, MaxHealth(3)
	, TimeToLaunch(3)
	, UnitCoordinates()
	, UnitFaction(EUnitFactions::Neutral)
	, UnitLayer(EUnitLayers::Ground)
	, UnitFlags()
	, StoredMinerals(0)
	, ConnectedCore(nullptr)
	, OnUpdateHealth()
	, OnGatherMinerals()
{
	UnitMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileMesh0"));
	RootComponent = UnitMesh;
}

void ADropPointUnit::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ADropPointUnit::TryLaunch() const
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

void ADropPointUnit::AddResources(const int32 Amount)
{
	if (ConnectedCore)
	{
		const int32 TotalAmount = StoredMinerals + Amount;
		ConnectedCore->AddResources(TotalAmount);
		StoredMinerals = 0;
		return;
	}
	StoredMinerals += Amount;
	OnGatherMinerals.Broadcast(Amount);
}

void ADropPointUnit::AdjustHealth(const int32 Amount)
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

float ADropPointUnit::TakeDamage(const float DamageAmount)
{
	AdjustHealth(-DamageAmount);
	return DamageAmount;
}

void ADropPointUnit::Die()
{
	if (ADropPointGameMode* Gamemode = Cast<ADropPointGameMode>(GetWorld()->GetAuthGameMode()))
	{
		Gamemode->RemoveUnit(this);
	}
	Destroy();
}

bool ADropPointUnit::DestroyUnit()
{
	return GetWorld()->DestroyActor(this);
}

void ADropPointUnit::HighlightUnit(const bool bOn) const
{
	UnitMesh->SetScalarParameterValueOnMaterials(TEXT("Highlighted"), static_cast<float>(bOn));
}

void ADropPointUnit::PostCreateUnit(class ADropPointGameMode* OwnerMode) const
{
	TArray<UDropPointSpawnComponent*> LogicComponents;
	GetComponents<UDropPointSpawnComponent>(LogicComponents);
	for (UDropPointSpawnComponent* LogicComponent : LogicComponents)
	{
		LogicComponent->Fire(OwnerMode, UnitCoordinates);
	}
}

void ADropPointUnit::SetUnitCoords(const FDropPointGridCoord& NewCoord)
{
	UnitCoordinates = NewCoord;
}

void ADropPointUnit::SetUnitFlag(const EUnitFlags Value)
{
	UnitFlags = (uint8)Value;
}

void ADropPointUnit::AddUnitFlag(const EUnitFlags Value)
{
	UnitFlags |= (uint8)Value;
}

void ADropPointUnit::RemoveUnitFlag(const EUnitFlags Value)
{
	UnitFlags &= ~(uint8)Value;
}

bool ADropPointUnit::HasUnitFlag(const EUnitFlags Value) const
{
	return UnitFlags & (uint8)Value;
}

