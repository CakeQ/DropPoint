// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DropPointEnums.h"
#include "DropPointUnit.generated.h"

UCLASS()
class DROPPOINT_API ADropPointUnit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADropPointUnit();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unit)
	EUnitFactions UnitFaction = EUnitFactions::Neutral;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unit)
	FString UnitName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unit)
	FString UnitDesc;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Unit)
	class UStaticMeshComponent* UnitMesh;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Unit)
	class ADropPointTile* ConnectedTile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unit)
	int32 Health = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unit)
	int32 MaxHealth = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unit)
	int32 TimeToLaunch = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unit)
	EUnitLayers UnitLayer = EUnitLayers::Ground;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unit)
	EUnitFlags UnitFlags = EUnitFlags::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unit)
	int32 StoredMinerals;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void TryLaunch();

	void TriggerAbilities();
	
	void AddMinerals(const int32& Amount);

	void AdjustHealth(const int32& Amount);

	// Override base actor TakeDamage
	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void Die();

	FORCEINLINE const int32 GetHealth() { return Health; };

	FORCEINLINE const int32 GetMaxHealth() { return MaxHealth; };

	FORCEINLINE const int32 GetTimeToLaunch() { return TimeToLaunch; };

	FORCEINLINE const EUnitFactions GetFaction() { return UnitFaction; };

	FORCEINLINE const EUnitLayers GetLayer() { return UnitLayer; };

	void SetConnectedTile(class ADropPointTile* Tile);

	FORCEINLINE class ADropPointTile* GetConnectedTile() { return ConnectedTile; };

	FORCEINLINE bool HasUnitFlag(EUnitFlags FlagType) { return (UnitFlags & FlagType) != EUnitFlags::None; };

	FORCEINLINE static bool FactionPredicate(const ADropPointUnit& u1, const ADropPointUnit& u2) { return (u1.UnitFaction > u2.UnitFaction); };

	FORCEINLINE void ChangeMaterial(UMaterialInstance* NewMaterial) { UnitMesh->SetMaterial(0, NewMaterial); };

	FORCEINLINE void GetThumbnail() { };

	FORCEINLINE const FString& GetName() { return UnitName; };

	FORCEINLINE const FString& GetDescription() { return UnitDesc; };
};
