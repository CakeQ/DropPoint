// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DropPointWidgetResources.generated.h"

/**
 * Simple UI counter for tracking the amount of resources collected throughout the game.
 */
UCLASS()
class DROPPOINT_API UDropPointWidgetResources : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(Category = Components, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_Resources;

	UPROPERTY(Category = Components, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_Spenditure;

	UPROPERTY(Category = Components, BlueprintReadOnly, meta = (BindWidget))
	class UProgressBar* ProgressBar_Resources;

	UPROPERTY(Category = DropPoint, EditAnywhere, BlueprintReadWrite)
	int32 ResourcesValue = 0;

	UPROPERTY(Category = DropPoint, EditAnywhere, BlueprintReadWrite)
	int32 SpentValue = 0;

	UPROPERTY(Category = DropPoint, EditAnywhere, BlueprintReadWrite)
	int32 BarMin = -250;

	UPROPERTY(Category = DropPoint, EditAnywhere, BlueprintReadWrite)
	int32 BarMax = 500;

public:
	UFUNCTION(Category = DropPoint, BlueprintCallable)
	void UpdateCounters();

	UFUNCTION(Category = DropPoint, BlueprintCallable)
	void SetResources(const int32& Value);

	UFUNCTION(Category = DropPoint, BlueprintCallable)
	void AddResources(const int32& Value);

	UFUNCTION(Category = DropPoint, BlueprintCallable)
	void SetSpenditure(const int32& Value);

	UFUNCTION(Category = DropPoint, BlueprintCallable)
	void AddSpenditure(const int32& Value);
};
