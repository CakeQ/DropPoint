// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.


#include "DropPointWidgetInventoryUnit.h"
#include "DropPointUnit.h"
#include "DropPointCharacter.h"
#include "Engine/Texture2D.h"
#include "Components/Button.h"
#include "Components/Image.h"

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
		Image_Thumbnail->SetBrushFromTexture(UnitType->GetThumbnail());
	}
	if (Button_Unit)
	{
		Button_Unit->SetToolTipText(FText::FromString(UnitType->GetName()));
	}
}

void UDropPointWidgetInventoryUnit::ActivateButton()
{
	if (PlayerCharacter && UnitType)
	{
		if (PlayerCharacter->GetUnitSpawnType() == UnitType->GetClass())
		{
			PlayerCharacter->SetUnitSpawnType(nullptr);
		}
		else
		{
			PlayerCharacter->SetUnitSpawnType(UnitType->GetClass());
		}
	}
}

