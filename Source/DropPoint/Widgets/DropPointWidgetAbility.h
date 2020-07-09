// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DropPointWidgetAbility.generated.h"

/**
 * 
 */
UCLASS()
class DROPPOINT_API UDropPointWidgetAbility : public UUserWidget
{
	GENERATED_BODY()

protected:
	/** Override to bind button clicking to ActivateButton() */
	virtual void NativeConstruct() override;

	/** The ability this button will pass to the unit when pressed. */
	UPROPERTY(Category = Classes, EditAnywhere, BlueprintReadWrite)
	class UDropPointAbility* Ability;

	/** The unit this button is bound to. */
	UPROPERTY(Category = References, EditAnywhere, BlueprintReadWrite)
	class ADropPointUnit* OwnerUnit;

	/** The button component. */
	UPROPERTY(Category = Components, BlueprintReadOnly, meta = (BindWidget))
	class UButton* Button_Ability;

	/** The image component that will display the ability thumbnail. */
	UPROPERTY(Category = Components, BlueprintReadOnly, meta = (BindWidget))
	class UImage* Image_Thumbnail;

public:
	/** Sets the ability this button will pass to the unit when pressed. */
	UFUNCTION(Category = DropPoint, BlueprintSetter)
	void SetAbilityType(class UDropPointAbility* NewType);

	/** Sets the unit this button is bound to. */
	FORCEINLINE UFUNCTION(Category = DropPoint, BlueprintSetter)
	void SetUnit(class ADropPointUnit* NewUnit) { OwnerUnit = NewUnit; };

	/** Tells the unit to use the ability this button is storing. */
	UFUNCTION(Category = DropPoint, BlueprintCallable)
	void ActivateButton();

	/** Gets the ability class type this button stores. */
	FORCEINLINE UFUNCTION(Category = DropPoint, BlueprintGetter)
	class UDropPointAbility* GetAbility() { return Ability; };
};