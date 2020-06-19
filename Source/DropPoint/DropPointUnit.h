// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DropPointUnit.generated.h"

UCLASS()
class DROPPOINT_API ADropPointUnit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADropPointUnit();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Unit)
	class UStaticMeshComponent* UnitMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unit)
	class UStaticMesh* BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unit)
	class UMaterialInstance* BaseMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unit)
	int32 Health = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unit)
	int32 MaxHealth = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unit)
	bool bInvulnerable = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unit)
	int32 TimeToLaunch = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Unit)
	TArray<int32> StoredResources; 

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AdjustHealth(int32 Amount);

	FORCEINLINE void TakeDamage(int32 Amount) { AdjustHealth(-Amount); };

	void Die();

	FORCEINLINE int32 GetHealth() { return Health; };

	FORCEINLINE int32 GetMaxHealth() { return MaxHealth; };

	FORCEINLINE int32 GetTimeToLaunch() { return TimeToLaunch; };
};
