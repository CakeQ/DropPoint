// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DropPointUnit.generated.h"

UENUM()
enum class EUnitFlags
{
	None,
	TakingOff		= 0x01,
	Overheating		= 0x02,
	Invulnerable	= 0x04
};
ENUM_CLASS_FLAGS(EUnitFlags)

UENUM()
enum class EFactions : uint8
{
	Player,
	Neutral,
	Hostile
};

UCLASS()
class DROPPOINT_API ADropPointUnit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADropPointUnit();

	EFactions Faction = EFactions::Neutral;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Unit)
	class UStaticMeshComponent* UnitMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unit)
	class UStaticMesh* BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unit)
	class UMaterialInstance* BaseMaterial;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unit)
	//int32 Health = 3;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unit)
	//int32 MaxHealth = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unit)
	EUnitFlags UnitFlags = EUnitFlags::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unit)
	int32 TimeToLaunch = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unit)
	TArray<TSubclassOf<class UDropPointAbility>> AbilityClasses;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Unit)
	TArray<class UDropPointAbility*> Abilities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unit)
	TArray<int32> StoredResources;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void TryLaunch();

	void TriggerAbilities();

	//FORCEINLINE int32 GetHealth() { return Health; };

	//FORCEINLINE int32 GetMaxHealth() { return MaxHealth; };

	FORCEINLINE int32 GetTimeToLaunch() { return TimeToLaunch; };

	FORCEINLINE bool HasUnitFlag(EUnitFlags FlagType) { return (UnitFlags & FlagType) != EUnitFlags::None; };

	FORCEINLINE static bool FactionPredicate(const ADropPointUnit& u1, const ADropPointUnit& u2) { return (u1.Faction > u2.Faction); };
};
