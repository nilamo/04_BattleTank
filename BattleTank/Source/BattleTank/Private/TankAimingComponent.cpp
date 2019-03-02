// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
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

	// ...
}

void UTankAimingComponent::AimAt(FVector TargetLocation, float LaunchSpeed)
{
	if (_Barrel && _Turret)
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

void UTankAimingComponent::MoveBarrelToward(FVector MoveTo)
{
	FRotator CurrentRotation = _Barrel->GetForwardVector().Rotation();
	FRotator DeltaRotation = MoveTo.Rotation() - CurrentRotation;
	_Barrel->Elevate(DeltaRotation.Pitch);

	FRotator CurrentAngle = _Turret->GetForwardVector().Rotation();
	FRotator DeltaAngle = MoveTo.Rotation() - CurrentAngle;
	_Turret->Spin(DeltaAngle.Yaw);
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * Barrel)
{
	_Barrel = Barrel;
}

void UTankAimingComponent::SetTurretReference(UTankTurret * Turret)
{
	_Turret = Turret;
}
