// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DropPointWidgetTurn.generated.h"

/**
 * 
 */
UCLASS()
class DROPPOINT_API UDropPointWidgetTurn : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = Turn)
	class UTextBlock* Text_TurnCounter;

	UFUNCTION()
	void UpdateTurn(const int32& value);
};
