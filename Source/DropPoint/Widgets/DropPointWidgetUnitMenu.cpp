// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.


#include "DropPointWidgetUnitMenu.h"
#include "../DropPointWidgetUnit.h"
#include "../DropPointUnit.h"
#include "Components/WrapBox.h"

void UDropPointWidgetUnitMenu::CreateButtons(TArray<TSubclassOf<ADropPointUnit>> Units)
{
	if (UnitButtonClass && Units.Num())
	{
		for (TSubclassOf<ADropPointUnit> UnitType : Units)
		{
			UDropPointWidgetUnit* NewButton = CreateWidget<UDropPointWidgetUnit>(GetWorld(), UnitButtonClass);
			NewButton->SetUnitType(UnitType);
			if (WrapBox_Units)
			{
				WrapBox_Units->AddChildToWrapBox(NewButton);
			}
		}
	}
}
