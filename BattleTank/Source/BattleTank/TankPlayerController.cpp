// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"

#define OUT

ATankPlayerController::ATankPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent))
	{
		FoundAimingComponent(AimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller cannot find aiming component."));
	}
}

void ATankPlayerController::SetPawn(APawn* Pawn)
{
	Super::SetPawn(Pawn);

	if (Pawn)
	{
		ATank* Tank = Cast<ATank>(Pawn);
		if (!ensure(Tank)) { return; }

		Tank->OnDeathEvent.AddUniqueDynamic(this, &ATankPlayerController::OnDeath);
	}
}

void ATankPlayerController::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);

	AimTowardsCursor();
}

void ATankPlayerController::AimTowardsCursor()
{
	APawn* Pawn = GetPawn();
	if (!Pawn) { return; }

	UTankAimingComponent* TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	// move the barrel a little closer to where the pointer's pointing
	if (!ensure(TankAimingComponent)) { return; }

	FVector HitLocation;
	bool HitFound = GetSightRayHitLocation(OUT HitLocation);
	if (HitFound)
	{
		TankAimingComponent->AimAt(HitLocation);
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
	}
	else
	{
		HitLocation = FVector::ZeroVector;
	}

	return true;
}

void ATankPlayerController::OnDeath()
{
	StartSpectatingOnly();
//	UE_LOG(LogTemp, Warning, TEXT("%f: Player dead :("), GetWorld()->GetTimeSeconds());
}