// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.


#include "DropPointWidgetUnit.h"
#include "DropPointUnit.h"
#include "DropPointCharacter.h"
#include "Engine/Texture2D.h"
#include "Components/Button.h"

void UDropPointWidgetUnit::NativeConstruct()
{
	Super::NativeConstruct();
	if (Button_Unit)
	{
		Button_Unit->OnClicked.AddDynamic(this, &UDropPointWidgetUnit::ActivateButton);
	}
}

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

void UDropPointWidgetUnit::ActivateButton()
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

