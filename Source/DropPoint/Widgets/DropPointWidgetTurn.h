// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DropPointWidgetTurn.generated.h"

/**
 * A user widget that creates a button that stores and outputs a unit type class to the player when clicked. Displays the unit's thumbnail as an image, and the unit's name as a tooltip.
 */
UCLASS()
class DROPPOINT_API UDropPointWidgetTurn : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	/** The text component that will display the current turn value. */
	UPROPERTY(Category = Components, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* Text_TurnCounter;

public:
	/**
	 * Updates the turn value.
	 * @param Value - The value to use.
	 */
	UFUNCTION(Category = DropPoint, BlueprintCallable)
	void UpdateTurn(const int32& Value);
};
