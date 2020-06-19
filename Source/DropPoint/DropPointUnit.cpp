// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.


#include "DropPointUnit.h"
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
}

// Called every frame
void ADropPointUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADropPointUnit::AdjustHealth(int32 Amount)
{
	if (bInvulnerable)
	{
		return;
	}
	Health = FMath::Clamp(Health + Amount, 0, MaxHealth);
	if (!Health)
	{
		Die();
	}
}

void ADropPointUnit::Die()
{

}