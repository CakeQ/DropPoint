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

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = UnitButton)
	class UWrapBox* WrapBox_Units;

	UPROPERTY(Category = DropPoint, EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UUserWidget> UnitButtonClass;

	TArray<class UCheckBox*> UnitButtons;

public:
	void CreateButtons(TArray<TSubclassOf<class ADropPointUnit>> Units);
};
