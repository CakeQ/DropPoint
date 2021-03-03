// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.


#include "DropPointWidgetInventoryUnit.h"
#include "DropPointUnit.h"
#include "DropPointCharacter.h"
#include "DropPointUnitItem.h"
#include "Engine/Texture2D.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UDropPointWidgetInventoryUnit::NativeConstruct()
{
	Super::NativeConstruct();
	if (Button_Unit)
	{
		Button_Unit->OnClicked.AddDynamic(this, &UDropPointWidgetInventoryUnit::ActivateButton);
	}
}

void UDropPointWidgetInventoryUnit::SetUnitType(TSubclassOf<class ADropPointUnit> NewType)
{
	UnitType = Cast<ADropPointUnit>(NewType->GetDefaultObject());
	if (Image_Thumbnail)
	{
		Image_Thumbnail->SetBrushFromTexture(UnitType->GetUnitThumbnail());
	}
	if (Button_Unit)
	{
		Button_Unit->SetToolTipText(FText::FromName(UnitType->GetUnitName()));
	}
}

void UDropPointWidgetInventoryUnit::SetPlayer(class ADropPointCharacter* Player)
{
	if (PlayerCharacter)
	{
		PlayerCharacter->OnUnitPlaced.RemoveDynamic(this, &UDropPointWidgetInventoryUnit::UpdateQuantity);
	}
	PlayerCharacter = Player;
	PlayerCharacter->OnUnitPlaced.AddDynamic(this, &UDropPointWidgetInventoryUnit::UpdateQuantity);
}

void UDropPointWidgetInventoryUnit::SetProperties(const FDropPointUnitItem& NewUnit, ADropPointCharacter* NewPlayer)
{
	SetUnitType(NewUnit.UnitType);
	SetUnitCost(NewUnit.Cost);
	SetUnitQuantity(NewUnit.Quantity);
	SetPlayer(NewPlayer);
}

void UDropPointWidgetInventoryUnit::SetUnitCost(const int32& Amount)
{
	UnitCost = Amount;
	if (TextBlock_Cost)
	{
		TextBlock_Cost->SetText(FText::Format(FText::FromString("{0}"), Amount));
	}
}

void UDropPointWidgetInventoryUnit::SetUnitQuantity(const int32& Amount)
{
	UnitQuantity = FMath::Max(Amount, 0);
	if (TextBlock_Quantity)
	{
		TextBlock_Quantity->SetText(FText::Format(FText::FromString("{0}"), UnitQuantity));
		if (UnitQuantity <= 0)
		{
			TextBlock_Quantity->SetVisibility(ESlateVisibility::Hidden);
			if (TextBlock_Cost)
			{
				TextBlock_Cost->SetVisibility(ESlateVisibility::HitTestInvisible);
			}
		}
		else
		{
			TextBlock_Quantity->SetVisibility(ESlateVisibility::HitTestInvisible);
			if (TextBlock_Cost)
			{
				TextBlock_Cost->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}
}

void UDropPointWidgetInventoryUnit::AdjustUnitQuantity(const int32& Amount)
{
	SetUnitQuantity(UnitQuantity + Amount);
}

void UDropPointWidgetInventoryUnit::UpdateQuantity(TSubclassOf<class ADropPointUnit> CompareType, const int32& Amount = -1)
{
	if (!UnitType || CompareType != UnitType->GetClass())
	{
		return;
	}

	AdjustUnitQuantity(Amount);
}

void UDropPointWidgetInventoryUnit::ActivateButton()
{
	if (PlayerCharacter && UnitType)
	{
		if (PlayerCharacter->GetUnitSpawnType() == UnitType->GetClass() || (!UnitQuantity && PlayerCharacter->GetMineralBudget() < UnitCost))
		{
			PlayerCharacter->SetUnitSpawnType(nullptr);
		}
		else
		{
			PlayerCharacter->SetUnitSpawnType(UnitType->GetClass());
		}
	}
}

