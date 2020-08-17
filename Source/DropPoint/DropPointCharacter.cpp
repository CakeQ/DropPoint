// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#include "DropPointCharacter.h"
#include "DrawDebugHelpers.h"
#include "DropPointGameMode.h"
#include "DropPointUnit.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialParameterCollectionInstance.h"
#include "Tiles/DropPointTile.h"
#include "Tiles/DropPointTileInteractive.h"
#include "Widgets/DropPointWidgetInventory.h"
#include "Widgets/DropPointWidgetResources.h"
#include "Widgets/DropPointWidgetUnit.h"

//#define PrintDebug(x) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT(x));}

ADropPointCharacter::ADropPointCharacter()
{
	GetCharacterMovement()->GravityScale = 0.0f;
	GetCharacterMovement()->bCheatFlying = true;
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
	GetCharacterMovement()->AirControl = 1.0f;
	GetCharacterMovement()->FallingLateralFriction = 4.0f;

	PawnSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	PawnSpringArm->SetupAttachment(RootComponent);
	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	PawnCamera->SetupAttachment(PawnSpringArm, USpringArmComponent::SocketName);

	//PawnCamera->SetProjectionMode(ECameraProjectionMode::Orthographic);
	PawnSpringArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	PawnSpringArm->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	if (PawnCamera->ProjectionMode == ECameraProjectionMode::Orthographic)
	{
		PawnSpringArm->TargetArmLength = 800.f;
		PawnCamera->OrthoWidth = 1500.0f;
	}
	else
	{
		PawnSpringArm->TargetArmLength = 3000.f;
		PawnCamera->FieldOfView = 35.0f;
	}
}

void ADropPointCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bPanCamera)
	{
		GetWorld()->GetGameViewport()->Viewport->SetMouse(PanX, PanY);
		return;
	}

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		FVector Start, Dir;
		PC->DeprojectMousePositionToWorld(Start, Dir);
		const FVector End = Start + (Dir * 30000.0f);
		TraceForBlock(Start, End, false);
	}
}

void ADropPointCharacter::NextAction()
{
	ADropPointGameMode* Gamemode = Cast<ADropPointGameMode>(GetWorld()->GetAuthGameMode());
	Gamemode->EndTurn();
}

void ADropPointCharacter::SetUnitSpawnType(TSubclassOf<class ADropPointUnit> NewType)
{
	UnitSpawnTypeClass = NewType;
	if (UnitSpawnTypeClass && CurrentActiveTile)
	{
		CurrentActiveTile->DeactivateTile();
		CurrentActiveTile = nullptr;
	}
}

void ADropPointCharacter::AddUnit(ADropPointUnit* NewUnit) const
{
	if(ResourcesWidget)
	{
		NewUnit->OnGatherMinerals.AddDynamic(ResourcesWidget, &UDropPointWidgetResources::AddResources);
	}
}

void ADropPointCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("TriggerClick", IE_Pressed, this, &ADropPointCharacter::TriggerClick);
	PlayerInputComponent->BindAction("MiddleClick", IE_Pressed, this, &ADropPointCharacter::EnablePan);
	PlayerInputComponent->BindAction("MiddleClick", IE_Released, this, &ADropPointCharacter::DisablePan);
	PlayerInputComponent->BindAction("NextAction", IE_Released, this, &ADropPointCharacter::NextAction);
	PlayerInputComponent->BindAxis("MoveX", this, &ADropPointCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MoveY", this, &ADropPointCharacter::MoveUp);
	PlayerInputComponent->BindAxis("PanX", this, &ADropPointCharacter::PanRight);
	PlayerInputComponent->BindAxis("PanY", this, &ADropPointCharacter::PanUp);
	PlayerInputComponent->BindAxis("ScrollZoom", this, &ADropPointCharacter::ScrollZoom);
}

void ADropPointCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (HighlightParameterCollection)
	{
		HighlightParameters = GetWorld()->GetParameterCollectionInstance(HighlightParameterCollection);
		if (PawnCamera->ProjectionMode == ECameraProjectionMode::Orthographic)
		{
			HighlightParameters->SetScalarParameterValue(TEXT("CameraZoom"), PawnCamera->OrthoWidth);
		}
		else
		{
			HighlightParameters->SetScalarParameterValue(TEXT("CameraZoom"), PawnSpringArm->TargetArmLength);
		}
	}

	if (UnitMenuWidgetClass)
	{
		UnitMenuWidget = CreateWidget<UDropPointWidgetUnit>(GetWorld(), UnitMenuWidgetClass);
		if (UnitMenuWidget)
		{
			UnitMenuWidget->AddToViewport();
			UnitMenuWidget->UpdateWidgets();
		}
	}

	if (UnitInventoryWidgetClass && UnitInventory.Num())
	{
		UnitInventoryWidget = CreateWidget<UDropPointWidgetInventory>(GetWorld(), UnitInventoryWidgetClass);
		if (UnitInventoryWidget)
		{
			UnitInventoryWidget->CreateButtons(UnitInventory, this);
			UnitInventoryWidget->AddToViewport();
		}
	}

	if (ResourcesWidgetClass)
	{
		ResourcesWidget = CreateWidget<UDropPointWidgetResources>(GetWorld(), ResourcesWidgetClass);
		if (ResourcesWidget)
		{
			ResourcesWidget->SetExpenditure(StartingExpenditure);
			ResourcesWidget->SetBudget(MineralsAvailable);
			ResourcesWidget->AddToViewport();
		}
	}
}

void ADropPointCharacter::TriggerClick()
{
	if (CurrentTileFocus)
	{
		OnTileSelect.Broadcast(CurrentTileFocus);
		if(HasPlayerFlag(EPlayerFlags::Targeting))
		{
			RemovePlayerFlag(EPlayerFlags::Targeting);
			return;
		}
		
		if (CurrentActiveTile)
		{
			CurrentActiveTile->DeactivateTile();
			if (CurrentTileFocus == CurrentActiveTile)
			{
				CurrentActiveTile = nullptr;
				if (UnitMenuWidget)
				{
					UnitMenuWidget->SetCurrentUnit(nullptr);
				}
				return;
			}
		}
		CurrentTileFocus->ActivateTile();
		CurrentActiveTile = CurrentTileFocus;
		if (HighlightParameters)
		{
			HighlightParameters->SetVectorParameterValue(TEXT("SelectedPos"), CurrentTileFocus->GetActorLocation());
		}
		if (UnitSpawnTypeClass)
		{
			ADropPointGameMode* Gamemode = Cast<ADropPointGameMode>(GetWorld()->GetAuthGameMode());
			if (Gamemode)
			{
				for (FDropPointUnitItem& UnitItem : UnitInventory)
				{
					if (UnitItem.UnitType == UnitSpawnTypeClass)
					{
						if (UnitItem.Cost > MineralsAvailable)
						{
							return;
						}
						break;
					}
				}

				ADropPointUnit* NewUnit = Gamemode->CreateUnit(CurrentTileFocus->GetTileCoords(), UnitSpawnTypeClass, PlayerFaction, false);

				if (!NewUnit)
				{
					UnitSpawnTypeClass = nullptr;
					return;
				}

				if (ResourcesWidget)
				{
					NewUnit->OnGatherMinerals.AddDynamic(ResourcesWidget, &UDropPointWidgetResources::AddResources);
				}

				for (FDropPointUnitItem& UnitItem : UnitInventory)
				{
					if (UnitItem.UnitType == UnitSpawnTypeClass)
					{
						if (!UnitItem.Quantity)
						{
							MineralsAvailable -= UnitItem.Cost;
							if (ResourcesWidget)
							{
								ResourcesWidget->AddBudget(-UnitItem.Cost);
							}
							OnPurchaseUnit.Broadcast(UnitItem.Cost);
							break;
						}
						UnitItem.SetQuantity(FMath::Max(UnitItem.Quantity - 1, 0));
						break;
					}
				}

				OnUnitPlaced.Broadcast(UnitSpawnTypeClass, -1);
				SetUnitSpawnType(nullptr);
			}
		}
		if (UnitMenuWidget)
		{
			if (CurrentActiveTile)
			{
				UnitMenuWidget->SetCurrentUnit(CurrentActiveTile->GetUnit(EUnitLayers::Ground));
			}
		}
	}
}

void ADropPointCharacter::ScrollZoom(float Value)
{
	if (PawnCamera->ProjectionMode == ECameraProjectionMode::Orthographic)
	{
		PawnCamera->OrthoWidth = FMath::Clamp(PawnCamera->OrthoWidth - (Value * 100.0f), 300.0f, 3000.0f);
		HighlightParameters->SetScalarParameterValue(TEXT("CameraZoom"), PawnCamera->OrthoWidth);
	}
	else
	{
		PawnSpringArm->TargetArmLength = FMath::Clamp(PawnSpringArm->TargetArmLength - (Value * 200.0f), 600.0f, 6000.0f);
		HighlightParameters->SetScalarParameterValue(TEXT("CameraZoom"), PawnSpringArm->TargetArmLength);
	}
}

void ADropPointCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ADropPointCharacter::MoveUp(float Value)
{
	if (Value != 0.0f)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ADropPointCharacter::EnablePan()
{
	bPanCamera = true;
	if (CurrentTileFocus)
	{
		CurrentTileFocus->HighlightTile(false);
	}
	PanX = GetWorld()->GetGameViewport()->Viewport->GetMouseX();
	PanY = GetWorld()->GetGameViewport()->Viewport->GetMouseY();
	UGameplayStatics::GetPlayerController(this, 0)->bShowMouseCursor = false;
}

void ADropPointCharacter::DisablePan()
{
	bPanCamera = false;
	UGameplayStatics::GetPlayerController(this, 0)->bShowMouseCursor = true;
}

void ADropPointCharacter::PanUp(float Value)
{
	if (!bPanCamera)
	{
		return;
	}

	MoveUp(GetWorld()->GetGameViewport()->Viewport->GetMouseY() - PanY);
}

void ADropPointCharacter::PanRight(float Value)
{
	if (!bPanCamera)
	{
		return;
	}

	MoveRight(PanX - GetWorld()->GetGameViewport()->Viewport->GetMouseX());
}

void ADropPointCharacter::TraceForBlock(const FVector& Start, const FVector& End, bool bDrawDebugHelpers)
{
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility);
	if (bDrawDebugHelpers)
	{
		DrawDebugLine(GetWorld(), Start, HitResult.Location, FColor::Red);
		DrawDebugSolidBox(GetWorld(), HitResult.Location, FVector(20.0f), FColor::Red);
	}
	if (HitResult.Actor.IsValid())
	{
		//Cast to the tile.
		ADropPointTileInteractive* HitTile = Cast<ADropPointTileInteractive>(HitResult.Actor.Get());

		//If the cast failed, try casting to any unit on top.
		if (!HitTile)
		{
			ADropPointUnit* HitUnit = Cast<ADropPointUnit>(HitResult.Actor.Get());
			if (HitUnit)
			{
				HitTile = Cast<ADropPointTileInteractive>(HitUnit->GetConnectedTile());
			}
		}

		//If we still fail to cast, just return.
		if (!HitTile)
		{
			return;
		}

		if (CurrentTileFocus != HitTile)
		{
			if (CurrentTileFocus)
			{
				CurrentTileFocus->HighlightTile(false);
			}
			if (HitTile)
			{
				HitTile->HighlightTile(true);
				if (HighlightParameters)
				{
					const FVector Loc = HitTile->GetActorLocation();
					HighlightParameters->SetVectorParameterValue(TEXT("MousePos"), Loc);
					if (!CurrentActiveTile)
					{
						HighlightParameters->SetVectorParameterValue(TEXT("SelectedPos"), Loc);
					}
				}
			}
			CurrentTileFocus = HitTile;
		}
	}
	else if (CurrentTileFocus)
	{
		CurrentTileFocus->HighlightTile(false);
		CurrentTileFocus = nullptr;
	}
}

void ADropPointCharacter::SetPlayerFlag(const EPlayerFlags& Value)
{
	PlayerFlags = (uint8)Value;
}

void ADropPointCharacter::AddPlayerFlag(const EPlayerFlags& Value)
{
	PlayerFlags |= (uint8)Value;
}

void ADropPointCharacter::RemovePlayerFlag(const EPlayerFlags& Value)
{
	PlayerFlags &= ~(uint8)Value;
}

bool ADropPointCharacter::HasPlayerFlag(const EPlayerFlags& Value) const
{
	return PlayerFlags & (uint8)Value;
}

