// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DropPointWidgetLevelDebug.generated.h"

/**
 * A debug-only widget used for regenerating the level.
 */
UCLASS()
class DROPPOINT_API UDropPointWidgetLevelDebug : public UUserWidget
{
	GENERATED_BODY()

protected:
	/** Text box for the level seed. */
	UPROPERTY(Category = Components, BlueprintReadOnly, meta = (BindWidget))
	class UEditableTextBox* TextBox_Seed;

	/** Button that will tell the gamemode to clear the arena. */
	UPROPERTY(Category = Components, BlueprintReadOnly, meta = (BindWidget))
	class UButton* Button_Clear;

	/** Button that will tell the gamemode to generate a level with the seed inputted in the text box. */
	UPROPERTY(Category = Components, BlueprintReadOnly, meta = (BindWidget))
	class UButton* Button_Generate;

public:
	/**
	 * Binds the widget to the input gamemode. Delegates the buttons to the gamemode's arena functions.
	 * @param GameMode - The input gamemode.
	 */
	void SetGameMode(class ADropPointGameMode* GameMode);
};
