// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.


#include "DropPointWidgetResources.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void UDropPointWidgetResources::SetResources(const int32& Value)
{
	MineralsValue = Value;
	if (TextBlock_Minerals)
	{
		TextBlock_Minerals->SetText(FText::Format(FText::FromString("{0} RUs"), MineralsValue - SpentValue));
	}
	if (ProgressBar_Minerals)
	{
		int32 NetAmount = FMath::Clamp(MineralsValue - SpentValue, BarMin, BarMax);
		double BarPercent = (double)(NetAmount - BarMin) / (double)(BarMax - BarMin);
		ProgressBar_Minerals->SetPercent(BarPercent);
	}
}

void UDropPointWidgetResources::AddResources(const int32& Value)
{
	SetResources(MineralsValue + Value);
}

void UDropPointWidgetResources::SetExpenditure(const int32& Value)
{
	SpentValue = Value;
	if (TextBlock_Spenditure)
	{
		TextBlock_Spenditure->SetText(FText::Format(FText::FromString("SPENT: {0}"), SpentValue));
	}
	if (TextBlock_Minerals)
	{
		TextBlock_Minerals->SetText(FText::Format(FText::FromString("{0} RUs"), MineralsValue - SpentValue));
	}
}

void UDropPointWidgetResources::AddExpenditure(const int32& Value)
{
	SetExpenditure(SpentValue + Value);
}

void UDropPointWidgetResources::SetBudget(const int32& Value)
{
	BudgetValue = FMath::Max(Value, 0);
	if (TextBlock_Budget)
	{
		TextBlock_Budget->SetText(FText::Format(FText::FromString("AVAILABLE: {0}"), BudgetValue));
	}
}

void UDropPointWidgetResources::AddBudget(const int32& Value)
{
	SetBudget(BudgetValue + Value);
}
