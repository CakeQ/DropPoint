// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.


#include "DropPointWidgetInventory.h"
#include "DropPointWidgetInventoryUnit.h"
#include "DropPointUnit.h"
#include "DropPointCharacter.h"
#include "Components/WrapBox.h"

void UDropPointWidgetInventory::CreateButtons(const TArray<FDropPointUnitItem>& Inventory, ADropPointCharacter* Player)
{
	if (!WrapBox_Units || !UnitButtonClass || !Inventory.Num() || !Player)
	{
		return;
	}

	UWorld* CurrentWorld = GetWorld();
	for (FDropPointUnitItem UnitItem : Inventory)
	{
		UDropPointWidgetInventoryUnit* NewButton = CreateWidget<UDropPointWidgetInventoryUnit>(CurrentWorld, UnitButtonClass);
		NewButton->SetProperties(UnitItem, Player);
		WrapBox_Units->AddChildToWrapBox(NewButton);
	}
}
