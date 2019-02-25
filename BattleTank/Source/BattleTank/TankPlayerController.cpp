// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"

#define OUT

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankPlayerController::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);

	AimTowardsCursor();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCursor()
{
	// move the barrel a little closer to where the pointer's pointing
	ATank* Tank = GetControlledTank();
	if (!Tank) { return; }

	FVector HitLocation;
	bool HitFound = GetSightRayHitLocation(OUT HitLocation);
	if (HitFound)
	{
		Tank->AimAt(HitLocation);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Crosshair looking off into space..."));
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	int32 ViewPortXSize, ViewPortYSize;
	GetViewportSize(OUT ViewPortXSize, OUT ViewPortYSize);

	FVector2D ScreenLocation = FVector2D(
		ViewPortXSize * CrosshairXLocation,
		ViewPortYSize * CrosshairYLocation
	);

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		bool bHitObject = GetLookVectorHitLocation(LookDirection, OUT HitLocation);
		return bHitObject;
	}

	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector & HitLocation) const
{
	FVector CameraLocation_Ignored;
	FVector WorldDirection;
	bool HitWorld = DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		OUT CameraLocation_Ignored,
		OUT WorldDirection
	);

	HitLocation = WorldDirection;
	return HitWorld;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookVector, FVector& HitLocation) const
{
	FVector CameraLocation = PlayerCameraManager->GetCameraLocation();
	FHitResult HitResult;
	bool HitFound = GetWorld()->LineTraceSingleByChannel(
		OUT HitResult,
		CameraLocation,
		CameraLocation + LookVector * LineTraceRange,
		ECollisionChannel::ECC_Visibility
	);

	if (HitFound)
	{
		HitLocation = HitResult.Location;
		return true;
	}

	return false;
}
