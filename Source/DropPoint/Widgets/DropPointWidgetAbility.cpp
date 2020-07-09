// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.


#include "DropPointWidgetAbility.h"
#include "DropPointAbility.h"
#include "DropPointCharacter.h"
#include "DropPointEnums.h"
#include "Engine/Texture2D.h"
#include "Components/Button.h"
#include "Components/Image.h"

void UDropPointWidgetAbility::NativeConstruct()
{
	Super::NativeConstruct();
	if (Button_Ability)
	{
		//Button_Ability->OnClicked.AddDynamic(this, &UDropPointWidgetAbility::ActivateButton);
	}
}

void UDropPointWidgetAbility::SetAbilityType(UDropPointAbility* NewType)
{
	Ability = NewType;
	if (Image_Thumbnail)
	{
		Image_Thumbnail->SetBrushFromTexture(Ability->GetThumbnail());
	}
	if (Button_Ability)
	{
		Button_Ability->SetToolTipText(FText::FromString(Ability->GetName()));
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
		else if(Ability->GetAbilityType() == EAbilityTypes::InstantTarget)
		{
			
		}
	}
}


