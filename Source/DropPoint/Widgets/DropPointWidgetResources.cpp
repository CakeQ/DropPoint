// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.


#include "DropPointWidgetResources.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void UDropPointWidgetResources::UpdateCounters()
{
	if (TextBlock_Minerals)
	{
		TextBlock_Minerals->SetText(FText::Format(FText::FromString("{0} RUs"), MineralsValue - SpentValue));
	}
	if (TextBlock_Spenditure)
	{
		TextBlock_Spenditure->SetText(FText::Format(FText::FromString("SPENT: {0}"), SpentValue));
	}
	if (ProgressBar_Minerals)
	{
		int32 NetAmount = FMath::Clamp(MineralsValue - SpentValue, BarMin, BarMax);
		double BarPercent = (double)(NetAmount - BarMin) / (double)(BarMax - BarMin);
		ProgressBar_Minerals->SetPercent(BarPercent);
	}
}

void UDropPointWidgetResources::SetResources(const int32& Value)
{
	MineralsValue = Value;
	UpdateCounters();
}

void UDropPointWidgetResources::AddResources(const int32& Value)
{
	MineralsValue += Value;
	UpdateCounters();
}

void UDropPointWidgetResources::SetExpenditure(const int32& Value)
{
	SpentValue = Value;
	UpdateCounters();
}

void UDropPointWidgetResources::AddExpenditure(const int32& Value)
{
	SpentValue += Value;
	UpdateCounters();
}
