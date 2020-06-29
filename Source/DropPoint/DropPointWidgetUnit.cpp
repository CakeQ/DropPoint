// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.


#include "DropPointWidgetUnit.h"
#include "DropPointUnit.h"
#include "Engine/Texture2D.h"
#include "Components/Button.h"

void UDropPointWidgetUnit::SetUnitType(TSubclassOf<class ADropPointUnit> NewType)
{
	UnitType = Cast<ADropPointUnit>(NewType->GetDefaultObject());
	if (Image_Thumbnail)
	{
		
	}
	if (Button_Unit)
	{
		Button_Unit->SetToolTipText(FText::FromString(UnitType->GetName()));
	}
}