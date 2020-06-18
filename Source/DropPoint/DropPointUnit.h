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

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
