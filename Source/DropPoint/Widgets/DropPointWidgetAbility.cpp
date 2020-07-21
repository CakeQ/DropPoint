// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.


#include "DropPointWidgetAbility.h"
#include "DropPointAbility.h"
#include "DropPointEnums.h"
#include "Components/Button.h"
#include "Components/Image.h"

void UDropPointWidgetAbility::NativeConstruct()
{
	Super::NativeConstruct();
}

void UDropPointWidgetAbility::SetAbilityType(UDropPointAbility* NewType)
{
	if (Ability)
	{
		//We shouldn't really be resetting a button's ability type, but just in case we don't want to trigger a runtime.
		Button_Ability->OnClicked.RemoveDynamic(this, &UDropPointWidgetAbility::ActivateButton);
	}
	Ability = NewType;
	if (Image_Thumbnail)
	{
		Image_Thumbnail->SetBrushFromTexture(Ability->GetThumbnail());
	}
	if (Button_Ability)
	{
		Button_Ability->SetToolTipText(FText::FromString(Ability->GetName()));
		Button_Ability->OnClicked.AddDynamic(this, &UDropPointWidgetAbility::ActivateButton);
	}
}

void UDropPointWidgetAbility::ActivateButton()
{
	if (OwnerUnit && Ability)
	{
		if (Ability->GetAbilityType() == EAbilityTypes::Instant)
		{
			Ability->QueueTrigger(OwnerUnit);
		}
		//Acquire target from player.
		else if(Ability->GetAbilityType() == EAbilityTypes::Targetable)
		{
			
		}
	}
}


