// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.


#include "DropPointWidgetInventory.h"
#include "DropPointWidgetInventoryUnit.h"
#include "DropPointUnit.h"
#include "DropPointCharacter.h"
#include "Components/WrapBox.h"

void UDropPointWidgetInventory::CreateButtons(TArray<TSubclassOf<ADropPointUnit>> Units, ADropPointCharacter* Player)
{
	if (UnitButtonClass && Units.Num())
	{
		for (TSubclassOf<ADropPointUnit> UnitType : Units)
		{
			UDropPointWidgetInventoryUnit* NewButton = CreateWidget<UDropPointWidgetInventoryUnit>(GetWorld(), UnitButtonClass);
			NewButton->SetUnitType(UnitType);
			NewButton->SetPlayer(Player);
			if (WrapBox_Units)
			{
				WrapBox_Units->AddChildToWrapBox(NewButton);
			}
		}
	}
}
