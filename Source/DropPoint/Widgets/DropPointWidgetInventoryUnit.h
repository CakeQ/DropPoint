// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DropPointWidgetInventoryUnit.generated.h"

/**
 * A user widget that displays an inventory of units that the player can use.
 */
UCLASS()
class DROPPOINT_API UDropPointWidgetInventoryUnit : public UUserWidget
{
	GENERATED_BODY()
protected:
	/** Override to bind button clicking to ActivateButton() */
	virtual void NativeConstruct() override;

	/** The unit type class this button will pass to the player when pressed. */
	UPROPERTY(Category = Classes, EditAnywhere, BlueprintReadWrite)
	class ADropPointUnit* UnitType;

	/** The player this button is bound to. */
	UPROPERTY(Category = References, EditAnywhere, BlueprintReadWrite)
	class ADropPointCharacter* PlayerCharacter;

	/** The button component. */
	UPROPERTY(Category = Components, BlueprintReadOnly, meta = (BindWidget))
	class UButton* Button_Unit;

	/** The image component that will display the unit thumbnail. */
	UPROPERTY(Category = Components, BlueprintReadOnly, meta = (BindWidget))
	class UImage* Image_Thumbnail;

public:
	/** Sets the unit type class this button will pass to the player when pressed. */
	UFUNCTION(Category = DropPoint, BlueprintSetter)
	void SetUnitType(TSubclassOf<class ADropPointUnit> NewType);

	/** Sets the player this button is bound to. */
	FORCEINLINE UFUNCTION(Category = DropPoint, BlueprintSetter)
	void SetPlayer(class ADropPointCharacter* Player) { PlayerCharacter = Player; };

	/** Tells the player to use the unit type class this button is storing. */
	UFUNCTION(Category = DropPoint, BlueprintCallable)
	void ActivateButton();

	/** Gets the unit class type this button stores. */
	FORCEINLINE UFUNCTION(Category = DropPoint, BlueprintGetter)
	class ADropPointUnit* GetUnitType() { return UnitType; };
};
