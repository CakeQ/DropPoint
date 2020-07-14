// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DropPointWidgetUnit.generated.h"

USTRUCT(BlueprintType)
struct DROPPOINT_API FDropPointUnitButtons
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = Buttons, EditAnywhere, BlueprintReadWrite)
	class ADropPointUnit* Parent;

	UPROPERTY(Category = Buttons, EditAnywhere, BlueprintReadWrite)
	TArray<class UDropPointWidgetAbility*> Buttons;
};

/**
 * 
 */
UCLASS()
class DROPPOINT_API UDropPointWidgetUnit : public UUserWidget
{
	GENERATED_BODY()

protected:
	/** The button class to use within the widget for standard abilities */
	UPROPERTY(Category = Classes, EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UUserWidget> AbilityButtonClassStandard;

	/** The button class to use within the widget for biome abilities */
	UPROPERTY(Category = Classes, EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UUserWidget> AbilityButtonClassBiome;

	/** The widget class for the health display */
	UPROPERTY(Category = Classes, EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UUserWidget> HealthWidgetClass;

	/** The unit this widget is bound to. */
	UPROPERTY(Category = References, EditAnywhere, BlueprintReadWrite)
	class ADropPointUnit* OwnerUnit;

	/** The container for all the standard ability buttons */
	UPROPERTY(Category = Components, BlueprintReadOnly, meta = (BindWidget))
		class UWrapBox* WrapBox_Abilities_Standard;

	/** The container for all the biome ability buttons */
	UPROPERTY(Category = Components, BlueprintReadOnly, meta = (BindWidget))
	class UWrapBox* WrapBox_Abilities_Biome;

	/** The text component that will display the unit name. */
	UPROPERTY(Category = Components, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_UnitName;

	/** The text component that will display the unit desc. */
	UPROPERTY(Category = Components, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_UnitDesc;

	/** The image component that will display the unit thumbnail. */
	UPROPERTY(Category = Components, BlueprintReadOnly, meta = (BindWidget))
	class UImage* Image_Thumbnail;

	/** The bar that will display the unit health. */
	UPROPERTY(Category = Components, BlueprintReadOnly, meta = (BindWidget))
	class UHorizontalBox* HorizontalBox_Health;

	/** The list of all ability buttons, stored per-unit in a struct */
	UPROPERTY(Category = Components, EditAnywhere, BlueprintReadOnly)
	TArray<FDropPointUnitButtons> AbilityButtons;

public:
	/**
	 * Sets the current active unit to display on the widget.
	 * @param Unit - The unit to pull data from.
	 */
	UFUNCTION(Category = DropPoint, BlueprintCallable)
	void SetCurrentUnit(class ADropPointUnit* Unit);

	/**
	 * Sets the current max health for the display.
	 * @param Value - The value to use.
	 */
	UFUNCTION(Category = DropPoint, BlueprintCallable)
	void UpdateMaxHealth(const int32& Value);

	/**
	 * Sets the current health for the display.
	 * @param Value - The value to use.
	 */
	UFUNCTION(Category = DropPoint, BlueprintCallable)
	void UpdateHealth(const int32& Value);

	/** Updates widget contents using current OwnerUnit. */
	UFUNCTION(Category = DropPoint, BlueprintCallable)
	void UpdateWidgets();

	/**
	 * Updates the current ability buttons visible based on the current OwnerUnit.
	 * Stores all unused ability buttons for other units for re-use.
	 */
	UFUNCTION(Category = DropPoint, BlueprintCallable)
	void UpdateButtons();
};
