// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2019  All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/GameModeBase.h"
#include "DropPointGameMode.generated.h"

UCLASS(minimalapi)
class ADropPointGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADropPointGameMode();

protected:
	UPROPERTY(Category = DropPoint, EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ArenaClass;

	UPROPERTY(Category = DropPoint, BlueprintReadOnly)
	class ADropPointArenaController* ArenaController;

	UPROPERTY(Category = DropPoint, EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> PlayerClass;

	UPROPERTY(Category = DropPoint, BlueprintReadOnly)
	class ADropPointCharacter* PlayerCharacter;

	UPROPERTY(Category = DropPoint, EditAnywhere, BlueprintReadOnly)
	int32 TurnCount = 0;

	UPROPERTY(Category = DropPoint, EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UUserWidget> TurnCountWidgetClass;

	UPROPERTY(Category = DropPoint, BlueprintReadOnly)
	class UDropPointWidgetTurn* TurnCountWidget;

public:
	virtual void BeginPlay() override;

	UFUNCTION(Category = DropPoint, BlueprintCallable)
	void EndTurn();
};



