// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DropPointWidgetUnitMenu.generated.h"

/**
 * 
 */
UCLASS()
class DROPPOINT_API UDropPointWidgetUnitMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	/** The button class to use within the widget */
	UPROPERTY(Category = Classes, EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UUserWidget> UnitButtonClass;

	/** The container for all the unit buttons */
	UPROPERTY(Category = Components, BlueprintReadOnly, meta = (BindWidget))
	class UWrapBox* WrapBox_Units;

	/** The list of all unit buttons */
	UPROPERTY(Category = Components, EditAnywhere, BlueprintReadOnly)
	TArray<class UCheckBox*> UnitButtons;

public:
	/**
	 * Creates a button for each unit class given to the function.
	 * @param Units - The list of all the unit classes to generate buttons for.
	 * @param Player - Reference to the player the button will be bound to. Used to tell the player what type of unit it should spawn after clicking the buttons.
	 */
	UFUNCTION(Category = DropPoint, BlueprintCallable)
	void CreateButtons(TArray<TSubclassOf<class ADropPointUnit>> Units, class ADropPointCharacter* Player);
};
