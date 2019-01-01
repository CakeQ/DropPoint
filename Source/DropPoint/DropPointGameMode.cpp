// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "DropPointGameMode.h"
#include "DropPointPlayerController.h"
#include "DropPointPawn.h"

ADropPointGameMode::ADropPointGameMode()
{
	// no pawn by default
	DefaultPawnClass = ADropPointPawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = ADropPointPlayerController::StaticClass();
}
