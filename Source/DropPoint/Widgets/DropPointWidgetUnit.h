// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DropPointWidgetUnit.generated.h"

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
	TSubclassOf<class UUserWidget> UnitButtonClassStandard;

	/** The button class to use within the widget for biome abilities */
	UPROPERTY(Category = Classes, EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UUserWidget> UnitButtonClassBiome;

	/** The unit this widget is bound to. */
	UPROPERTY(Category = References, EditAnywhere, BlueprintReadWrite)
	class ADropPointUnit* OwnerUnit;

	/** The container for all the standard ability buttons */
	UPROPERTY(Category = Components, BlueprintReadOnly, meta = (BindWidget))
	class UWrapBox* WrapBox_Abilities_Standard;

	/** The text component that will display the unit name. */
	UPROPERTY(Category = Components, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* Text_UnitName;

	/** The text component that will display the unit desc. */
	UPROPERTY(Category = Components, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* Text_UnitDesc;

	/** The image component that will display the unit thumbnail. */
	UPROPERTY(Category = Components, BlueprintReadOnly, meta = (BindWidget))
	class UImage* Image_Thumbnail;

	/** The bar that will display the unit health. */
	UPROPERTY(Category = Components, BlueprintReadOnly, meta = (BindWidget))
	class UProgressBar* Bar_Health;

	/** The container for all the biome ability buttons */
	UPROPERTY(Category = Components, BlueprintReadOnly, meta = (BindWidget))
	class UWrapBox* WrapBox_Abilities_Biome;

	/** The list of all ability buttons */
	UPROPERTY(Category = Components, EditAnywhere, BlueprintReadOnly)
	TArray<class UCheckBox*> AbilityButtons;

public:
	/**
	 * Sets the current active unit to display on the widget.
	 * @param Unit - The unit to pull data from.
	 */
	UFUNCTION(Category = DropPoint, BlueprintCallable)
	void SetCurrentUnit(class ADropPointUnit* Unit);
};
