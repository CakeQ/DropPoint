// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.


#include "DropPointWidgetHealth.h"
#include "Components/Image.h"

void UDropPointWidgetHealth::SetState(bool bOn)
{
	if (bOn)
	{
		Image_Status->SetBrushFromTexture(TextureOn);
	}
	else
	{
		Image_Status->SetBrushFromTexture(TextureOff);
	}
}
