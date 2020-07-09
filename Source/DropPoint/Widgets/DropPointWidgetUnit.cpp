// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.


#include "DropPointWidgetUnit.h"
#include "DropPointUnit.h"
#include "Widgets/DropPointWidgetAbility.h"
#include "DropPointAbility.h"
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/HorizontalBox.h"

void UDropPointWidgetUnit::SetCurrentUnit(class ADropPointUnit* Unit)
{
	if (OwnerUnit == Unit)
	{
		return;
	}

	//Unbind existing bindings.
	if (OwnerUnit)
	{
		OwnerUnit->OnUpdateHealth.RemoveDynamic(this, &UDropPointWidgetUnit::UpdateHealth);
	}

	OwnerUnit = Unit;

	if (OwnerUnit)
	{
		OwnerUnit->OnUpdateHealth.AddDynamic(this, &UDropPointWidgetUnit::UpdateHealth);
	}

	UpdateWidgets();
	UpdateButtons();
}

void UDropPointWidgetUnit::UpdateHealth(const int32& Value)
{
	if (ProgressBar_Health)
	{
		ProgressBar_Health->SetPercent(OwnerUnit->GetHealth() / OwnerUnit->GetMaxHealth());
	}
}

void UDropPointWidgetUnit::UpdateWidgets()
{
	if (!OwnerUnit)
	{
		SetVisibility(ESlateVisibility::Hidden);
		return;
	}
	else
	{
		SetVisibility(ESlateVisibility::Visible);
	}

	if (TextBlock_UnitName)
	{
		TextBlock_UnitName->SetText(FText::FromString(OwnerUnit->GetName()));
	}
	if (TextBlock_UnitDesc)
	{
		TextBlock_UnitDesc->SetText(FText::FromString(OwnerUnit->GetDescription()));
	}
	if (Image_Thumbnail)
	{
		Image_Thumbnail->SetBrushFromTexture(OwnerUnit->GetThumbnail());
	}
}

void UDropPointWidgetUnit::UpdateButtons()
{
	if (WrapBox_Abilities_Standard)
	{
		WrapBox_Abilities_Standard->ClearChildren();
	}

	if (WrapBox_Abilities_Biome)
	{
		WrapBox_Abilities_Biome->ClearChildren();
	}

	if (!OwnerUnit || OwnerUnit->GetFaction() != EUnitFactions::Player)
	{
		return;
	}

	FDropPointUnitButtons ButtonSet;

	bool bFound = false;
	for (FDropPointUnitButtons UnitButtons : AbilityButtons)
	{
		if (UnitButtons.Parent == OwnerUnit)
		{
			ButtonSet = UnitButtons;
			bFound = true;
			break;
		}
	}

	if (!bFound)
	{
		ButtonSet.Parent = OwnerUnit;
		TArray<UDropPointAbility*> Abilities;
		OwnerUnit->GetComponents<UDropPointAbility>(Abilities);

		for (UDropPointAbility* UnitAbility : Abilities)
		{
			UDropPointWidgetAbility* NewAbilityButton;
			switch (UnitAbility->GetAbilityCategory())
			{
			case EAbilityCats::Biome:
				NewAbilityButton = CreateWidget<UDropPointWidgetAbility>(GetWorld(), AbilityButtonClassBiome);
				break;
			default:
				NewAbilityButton = CreateWidget<UDropPointWidgetAbility>(GetWorld(), AbilityButtonClassStandard);
			}
			if (NewAbilityButton)
			{
				NewAbilityButton->SetAbilityType(UnitAbility);
				NewAbilityButton->SetUnit(OwnerUnit);
				ButtonSet.Buttons.Add(NewAbilityButton);
			}
		}
		AbilityButtons.Add(ButtonSet);
	}

	for (UDropPointWidgetAbility* ButtonToAdd : ButtonSet.Buttons)
	{
		switch (ButtonToAdd->GetAbility()->GetAbilityCategory())
		{
		case EAbilityCats::Biome:
			if (WrapBox_Abilities_Biome)
			{
				WrapBox_Abilities_Biome->AddChildToWrapBox(ButtonToAdd);
			}
			break;
		default:
			if (WrapBox_Abilities_Standard)
			{
				WrapBox_Abilities_Standard->AddChildToWrapBox(ButtonToAdd);
			}
		}
	}
}
