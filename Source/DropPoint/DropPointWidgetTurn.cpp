// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.


#include "DropPointWidgetTurn.h"
#include "Components/TextBlock.h"

void UDropPointWidgetTurn::NativeConstruct()
{
	Super::NativeConstruct();
}

void UDropPointWidgetTurn::UpdateTurn(const int32& value)
{
	if (Text_TurnCounter)
	{
		Text_TurnCounter->SetText(FText::Format(FText::FromString("Turn: {0}"), value));
	}
}
