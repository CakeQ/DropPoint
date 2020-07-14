// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DropPointUnitItem.h"
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

	/** The amount of this unit the player has in their inventory. */
	UPROPERTY(Category = Classes, EditAnywhere, BlueprintReadWrite)
	int32 UnitQuantity;

	/** The unit cost if the player has none of this unit in their inventory. */
	UPROPERTY(Category = Classes, EditAnywhere, BlueprintReadWrite)
	int32 UnitCost;

	/** The player this button is bound to. */
	UPROPERTY(Category = References, EditAnywhere, BlueprintReadWrite)
	class ADropPointCharacter* PlayerCharacter;

	/** The button component. */
	UPROPERTY(Category = Components, BlueprintReadOnly, meta = (BindWidget))
	class UButton* Button_Unit;

	/** The image component that will display the unit thumbnail. */
	UPROPERTY(Category = Components, BlueprintReadOnly, meta = (BindWidget))
	class UImage* Image_Thumbnail;

	/** The image component that will display the player's inventory's unit quantity. */
	UPROPERTY(Category = Components, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_Quantity;

	/** The image component that will display the unit cost. */
	UPROPERTY(Category = Components, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* TextBlock_Cost;

public:
	/** Sets the unit type class this button will pass to the player when pressed. */
	UFUNCTION(Category = DropPoint, BlueprintSetter)
	void SetUnitType(TSubclassOf<class ADropPointUnit> NewType);

	/** Sets the player this button is bound to. */
	UFUNCTION(Category = DropPoint, BlueprintSetter)
	void SetPlayer(class ADropPointCharacter* Player);

	/** Sets the unit cost. */
	UFUNCTION(Category = DropPoint, BlueprintCallable)
	void SetUnitCost(const int32& Amount);

	/** Sets the unit quantity amount. */
	UFUNCTION(Category = DropPoint, BlueprintSetter)
	void SetUnitQuantity(const int32& Amount);

	/** Adjusts the unit quantity amount. */
	UFUNCTION(Category = DropPoint, BlueprintCallable)
	void AdjustUnitQuantity(const int32& Amount);

	/** Delegate cast function that checks sent class type to confirm quantity amount reduction. */
	UFUNCTION(Category = DropPoint, BlueprintCallable)
	void UpdateQuantity(TSubclassOf<class ADropPointUnit> CompareType, const int32& Amount);

	/** Tells the player to use the unit type class this button is storing. */
	UFUNCTION(Category = DropPoint, BlueprintCallable)
	void ActivateButton();

	/** Gets the unit class type this button stores. */
	FORCEINLINE UFUNCTION(Category = DropPoint, BlueprintGetter)
	class ADropPointUnit* GetUnitType() { return UnitType; };
};
