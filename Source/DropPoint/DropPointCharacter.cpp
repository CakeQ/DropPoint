// Copyright Daniel Thompson @ https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#include "DropPointCharacter.h"
#include "DropPointGameMode.h"
#include "DropPointGridCoord.h"
#include "Tiles/DropPointTile.h"
#include "Tiles/DropPointTileInteractive.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

#define PrintDebug(x) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT(x));}

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

	if (HighlightParameterCollection)
	{
		HighlightParameters = GetWorld()->GetParameterCollectionInstance(HighlightParameterCollection);
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
		if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		{
			if (UCameraComponent* OurCamera = PC->GetViewTarget()->FindComponentByClass<UCameraComponent>())
			{
				FVector Start = OurCamera->GetComponentLocation();
				FVector End = Start + (OurCamera->GetComponentRotation().Vector() * 30000.0f);
				TraceForBlock(Start, End, true);
			}
		}
		else
		{
			FVector Start, Dir, End;
			PC->DeprojectMousePositionToWorld(Start, Dir);
			End = Start + (Dir * 30000.0f);
			TraceForBlock(Start, End, false);
		}
	}
}

void ADropPointCharacter::NextAction()
{
	ADropPointGameMode* gamemode = Cast<ADropPointGameMode>(GetWorld()->GetAuthGameMode());
	gamemode->EndTurn();
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
	}
}

void ADropPointCharacter::TriggerClick()
{
	if (CurrentTileFocus)
	{
		if (CurrentActiveTile)
		{
			CurrentActiveTile->DeactivateTile();
			if (CurrentTileFocus == CurrentActiveTile)
			{
				CurrentActiveTile = nullptr;
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
			ADropPointGameMode* gamemode = Cast<ADropPointGameMode>(GetWorld()->GetAuthGameMode());
			if (gamemode)
			{
				gamemode->CreateUnit(CurrentTileFocus->GetGridCoords(), UnitSpawnTypeClass, false);
			}
		}
	}
}

void ADropPointCharacter::ScrollZoom(float Value)
{
	if (PawnCamera->ProjectionMode == ECameraProjectionMode::Orthographic)
	{
		PawnCamera->OrthoWidth = FMath::Clamp(PawnCamera->OrthoWidth - (Value * 100.0f), 300.0f, 3000.0f);
	}
	else
	{
		PawnSpringArm->TargetArmLength = FMath::Clamp(PawnSpringArm->TargetArmLength - (Value * 200.0f), 600.0f, 6000.0f);
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
	GetWorld()->GetGameViewport()->Viewport->LockMouseToViewport(true);
	PanX = GetWorld()->GetGameViewport()->Viewport->GetMouseX();
	PanY = GetWorld()->GetGameViewport()->Viewport->GetMouseY();
	UGameplayStatics::GetPlayerController(this, 0)->bShowMouseCursor = false;
}

void ADropPointCharacter::DisablePan()
{
	bPanCamera = false;
	UGameplayStatics::GetPlayerController(this, 0)->bShowMouseCursor = true;
	GetWorld()->GetGameViewport()->Viewport->LockMouseToViewport(false);
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
		ADropPointTileInteractive* hitTile = Cast<ADropPointTileInteractive>(HitResult.Actor.Get());
		if (CurrentTileFocus != hitTile)
		{
			if (CurrentTileFocus)
			{
				CurrentTileFocus->HighlightTile(false);
			}
			if (hitTile)
			{
				hitTile->HighlightTile(true);
				if (HighlightParameters)
				{
					FVector loc = hitTile->GetActorLocation();
					HighlightParameters->SetVectorParameterValue(TEXT("MousePos"), loc);
					if (!CurrentActiveTile)
					{
						HighlightParameters->SetVectorParameterValue(TEXT("SelectedPos"), loc);
					}
				}
			}
			CurrentTileFocus = hitTile;
		}
	}
	else if (CurrentTileFocus)
	{
		CurrentTileFocus->HighlightTile(false);
		CurrentTileFocus = nullptr;
	}
}