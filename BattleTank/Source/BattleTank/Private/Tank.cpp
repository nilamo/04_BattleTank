// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankMovementComponent.h"
#include "Engine/World.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

void ATank::Fire()
{
	bool bIsReloaded = (FPlatformTime::Seconds() - LastFireTime) > TimeToReload;

	if (bIsReloaded && TankAimingComponent)
	{
		auto LaunchLocation = TankAimingComponent->GetLaunchLocation();

		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBP,
			LaunchLocation.Location,
			LaunchLocation.Rotation
		);

		Projectile->Launch(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

void ATank::AimAt(FVector TargetLocation)
{
	if (TankAimingComponent)
	{
		TankAimingComponent->AimAt(TargetLocation, LaunchSpeed);
	}
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

