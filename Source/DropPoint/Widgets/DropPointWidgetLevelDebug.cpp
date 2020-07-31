// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.


#include "DropPointWidgetLevelDebug.h"
#include "DropPointGameMode.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"

void UDropPointWidgetLevelDebug::SetGameMode(ADropPointGameMode* GameMode)
{
	if(TextBox_Seed)
	{
		TextBox_Seed->SetText(FText::FromString(GameMode->GetSeed()));
		TextBox_Seed->OnTextChanged.AddDynamic(GameMode, &ADropPointGameMode::SetSeed);
	}
	if(Button_Clear)
	{
		Button_Clear->OnClicked.AddDynamic(GameMode, &ADropPointGameMode::ClearArena);
	}
	if(Button_Generate)
	{
		Button_Generate->OnClicked.AddDynamic(GameMode, &ADropPointGameMode::RegenerateArena);
	}
}
