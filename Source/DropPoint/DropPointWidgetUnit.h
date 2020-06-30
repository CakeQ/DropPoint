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
	virtual void NativeConstruct() override;

	class ADropPointUnit* UnitType;

	class ADropPointCharacter* PlayerCharacter;

public:
	void SetUnitType(TSubclassOf<class ADropPointUnit> NewType);

	FORCEINLINE void SetPlayer(class ADropPointCharacter* Player) { PlayerCharacter = Player; };

	UFUNCTION()
	void ActivateButton();

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = UnitButton)
	class UButton* Button_Unit;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = UnitButton)
	class UImage* Image_Thumbnail;
	
	FORCEINLINE class ADropPointUnit* GetUnitType() { return UnitType; };
};
