// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.


#include "DropPointWidgetUnit.h"
#include "DropPointUnit.h"
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"

void UDropPointWidgetUnit::SetCurrentUnit(class ADropPointUnit* Unit)
{
	if (Unit)
	{
		SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
	OwnerUnit = Unit;

	if (!OwnerUnit)
	{
		return;
	}

	if (Text_UnitName)
	{
		Text_UnitName->SetText(FText::FromString(OwnerUnit->GetName()));
	}
	if (Text_UnitDesc)
	{
		Text_UnitDesc->SetText(FText::FromString(OwnerUnit->GetDesc()));
	}
	if (Image_Thumbnail)
	{
		Image_Thumbnail->SetBrushFromTexture(OwnerUnit->GetThumbnail());
	}
	if (Bar_Health)
	{
		Bar_Health->SetPercent(OwnerUnit->GetHealth() / OwnerUnit->GetMaxHealth());
	}
}
