// Copyright Daniel Thompson https://github.com/CakeQ and Archie Whitehead 2020 All Rights Reserved.

#include "DropPointCharacter.h"
#include "Tiles/DropPointTile.h"
#include "Tiles/DropPointTileInteractive.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
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
	PawnSpringArm->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	PawnSpringArm->TargetArmLength = 800.f;
	PawnSpringArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	PawnSpringArm->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	PawnCamera->SetupAttachment(PawnSpringArm, USpringArmComponent::SocketName);
	PawnCamera->SetProjectionMode(ECameraProjectionMode::Orthographic);
	PawnCamera->OrthoWidth = 1500.0f;
	PawnCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

void ADropPointCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		{
			if (UCameraComponent* OurCamera = PC->GetViewTarget()->FindComponentByClass<UCameraComponent>())
			{
				FVector Start = OurCamera->GetComponentLocation();
				FVector End = Start + (OurCamera->GetComponentRotation().Vector() * 8000.0f);
				TraceForBlock(Start, End, true);
			}
		}
		else
		{
			FVector Start, Dir, End;
			PC->DeprojectMousePositionToWorld(Start, Dir);
			End = Start + (Dir * 8000.0f);
			TraceForBlock(Start, End, false);
		}
	}
}

void ADropPointCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("TriggerClick", IE_Pressed, this, &ADropPointCharacter::TriggerClick);
	PlayerInputComponent->BindAxis("MoveX", this, &ADropPointCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MoveY", this, &ADropPointCharacter::MoveUp);
	PlayerInputComponent->BindAxis("ScrollZoom", this, &ADropPointCharacter::ScrollZoom);
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
	}
}

void ADropPointCharacter::ScrollZoom(float Value)
{
	PawnCamera->OrthoWidth = FMath::Clamp(PawnCamera->OrthoWidth - (Value * 100.0f), 300.0f, 3000.0f);
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