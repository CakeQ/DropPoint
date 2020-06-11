// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.


#include "DropPointWidgetTurn.h"
#include "Components/TextBlock.h"

void UDropPointWidgetTurn::NativeConstruct()
{
	Super::NativeConstruct();
}

void UDropPointWidgetTurn::SetCountValue(const int32& value)
{
	TurnCount = value;
	UpdateTurn();
}

void UDropPointWidgetTurn::UpdateTurn()
{
	if (TurnText)
	{
		TurnText->SetText(FText::Format(FText::FromString("Turn: {0}"), TurnCount));
	}
}
