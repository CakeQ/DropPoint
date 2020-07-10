// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.


#include "DropPointWidgetResources.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void UDropPointWidgetResources::UpdateCounters()
{
	if (TextBlock_Resources)
	{
		TextBlock_Resources->SetText(FText::Format(FText::FromString("{0} RUs"), ResourcesValue));
	}
	if (TextBlock_Spenditure)
	{
		TextBlock_Spenditure->SetText(FText::Format(FText::FromString("SPENT: {0}"), SpentValue));
	}
	if (ProgressBar_Resources)
	{
		int32 NetAmount = FMath::Clamp(ResourcesValue - SpentValue, BarMin, BarMax);
		ProgressBar_Resources->SetPercent(NetAmount / (BarMax - BarMin));
	}
}

void UDropPointWidgetResources::SetResources(const int32& Value)
{
	ResourcesValue = Value;
	UpdateCounters();
}

void UDropPointWidgetResources::AddResources(const int32& Value)
{
	ResourcesValue += Value;
	UpdateCounters();
}

void UDropPointWidgetResources::SetSpenditure(const int32& Value)
{
	SpentValue = Value;
	UpdateCounters();
}

void UDropPointWidgetResources::AddSpenditure(const int32& Value)
{
	SpentValue += Value;
	UpdateCounters();
}
