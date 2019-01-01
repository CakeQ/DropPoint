// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "DropPointPlayerController.h"

ADropPointPlayerController::ADropPointPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}
