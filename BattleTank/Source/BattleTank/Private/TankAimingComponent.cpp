// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	bool bIsReloaded = (FPlatformTime::Seconds() - LastFireTime) > TimeToReload;
	if (bIsReloaded)
	{
		if (IsBarrelMoving())
		{
			FiringStatus = EFiringStatus::Aiming;
		}
		else
		{
			FiringStatus = EFiringStatus::Locked;
		}
	}
	else
	{
		FiringStatus = EFiringStatus::Reloading;
	}
}

void UTankAimingComponent::Initialize(UTankBarrel * Barrel, UTankTurret * Turret)
{
	_Barrel = Barrel;
	_Turret = Turret;
}

void UTankAimingComponent::AimAt(FVector TargetLocation)
{
	if (ensure(_Barrel && _Turret))
	{
		// StaticMeshComponent
		FVector BarrelLocation = _Barrel->GetSocketLocation(FName("Projectile"));

		// gameplaystatics.h
		FVector SuggestedVelocity;
		TArray<AActor*> ActorsToIgnore;
		bool VelocityFound = UGameplayStatics::SuggestProjectileVelocity(
			this,
			OUT SuggestedVelocity,
			BarrelLocation,
			TargetLocation,
			LaunchSpeed,
			false,
			0,
			0,
			ESuggestProjVelocityTraceOption::DoNotTrace
			/*,
			FCollisionResponseParams::DefaultResponseParam,
			ActorsToIgnore,
			true*/
		);

		if (VelocityFound)
		{
			FVector Normal = SuggestedVelocity.GetSafeNormal();
			MoveBarrelToward(Normal);
		}
	}
}

void UTankAimingComponent::Fire()
{
	if (FiringStatus!=EFiringStatus::Reloading && ensure(ProjectileBP))
	{
		auto LaunchLocation = GetLaunchLocation();

		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBP,
			LaunchLocation.Location,
			LaunchLocation.Rotation
			);

		Projectile->Launch(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

EFiringStatus UTankAimingComponent::GetFiringState() const
{
	return FiringStatus;
}

ProjectileLaunchLocation UTankAimingComponent::GetLaunchLocation()
{
	ProjectileLaunchLocation LaunchFrom;
	LaunchFrom.Location = _Barrel->GetSocketLocation(FName("Projectile"));
	LaunchFrom.Rotation = _Barrel->GetSocketRotation(FName("Projectile"));
	return LaunchFrom;
}

void UTankAimingComponent::MoveBarrelToward(FVector MoveTo)
{
	if (!ensure(_Barrel && _Turret)) { return; }

	CurrentlyAimingTo = MoveTo;

	FRotator CurrentRotation = _Barrel->GetForwardVector().Rotation();
	FRotator DeltaRotation = MoveTo.Rotation() - CurrentRotation;
	_Barrel->Elevate(DeltaRotation.Pitch);

	FRotator CurrentAngle = _Turret->GetForwardVector().Rotation();
	FRotator DeltaAngle = MoveTo.Rotation() - CurrentAngle;
	float Rotation = DeltaAngle.Yaw;
	if (FMath::Abs(Rotation) > 180)
	{
		Rotation *= -1;
	}

	_Turret->Spin(Rotation);
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(_Barrel)) { return false; }

	FVector CurrentDirection = _Barrel->GetForwardVector();
	return !CurrentDirection.Equals(CurrentlyAimingTo, 0.01);;
}
