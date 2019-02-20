// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

#define OUT

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Player Controller Start"));
	ATank* Tank = GetControlledTank();
	if (Tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller with Tank: %s"), *(Tank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No tank :("));
	}
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
		UE_LOG(LogTemp, Warning, TEXT("Crosshair pointing at: %s"), *HitLocation.ToString());
	}
}

bool ATankPlayerController::GetSightRayHitLocation(OUT FVector& HitLocation) const
{
	int32 ViewPortXSize, ViewPortYSize;
	GetViewportSize(OUT ViewPortXSize, OUT ViewPortYSize);

	FVector2D ScreenLocation = FVector2D(
		ViewPortXSize * CrosshairXLocation,
		ViewPortYSize * CrosshairYLocation
	);

	return false;
}