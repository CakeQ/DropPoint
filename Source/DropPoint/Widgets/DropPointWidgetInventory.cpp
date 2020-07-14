// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.


#include "DropPointWidgetInventory.h"
#include "DropPointWidgetInventoryUnit.h"
#include "DropPointUnit.h"
#include "DropPointCharacter.h"
#include "Components/WrapBox.h"

void UDropPointWidgetInventory::CreateButtons(TArray<FDropPointUnitItem> Inventory, ADropPointCharacter* Player)
{
	if (UnitButtonClass && Inventory.Num())
	{
		for (FDropPointUnitItem UnitItem : Inventory)
		{
			UDropPointWidgetInventoryUnit* NewButton = CreateWidget<UDropPointWidgetInventoryUnit>(GetWorld(), UnitButtonClass);
			NewButton->SetUnitType(UnitItem.UnitType);
			NewButton->SetUnitQuantity(UnitItem.Quantity);
			NewButton->SetUnitCost(UnitItem.Cost);
			NewButton->SetPlayer(Player);
			if (WrapBox_Units)
			{
				WrapBox_Units->AddChildToWrapBox(NewButton);
			}
		}
	}
}
