// Copyright Daniel Thompson https://github.com/CakeQ and Archie Whitehead 2019  All Rights Reserved.

#include "DropPointGameMode.h"
#include "DropPointPlayerController.h"
#include "DropPointCharacter.h"
#include "DropPointArenaController.h"
#include "Engine/World.h"

ADropPointGameMode::ADropPointGameMode()
{

}

void ADropPointGameMode::BeginPlay()
{
	Super::BeginPlay();
	if (ArenaClass)
	{
		ArenaController = GetWorld()->SpawnActor<ADropPointArenaController>(ArenaClass.GetDefaultObject()->GetClass(), FVector(0, 0, 0), FRotator(0, 0, 0));
	}
	if (DefaultPawnClass)
	{
		//PlayerCharacter = GetWorld()->SpawnActor<ADropPointCharacter>(DefaultPawnClass.GetDefaultObject()->GetClass(), FVector(0, 0, 0), FRotator(0, 0, 0));
		GetWorld()->SpawnActor<AActor>(DefaultPawnClass.GetDefaultObject()->GetClass(), FVector(0, 0, 0), FRotator(0, 0, 0));
	}
}

void ADropPointGameMode::EndTurn()
{
	if (ArenaController)
	{
		ArenaController->EndTurn();
	}
}
