// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
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
	if (_Barrel)
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
			ESuggestProjVelocityTraceOption::TraceFullPath,
			FCollisionResponseParams::DefaultResponseParam,
			ActorsToIgnore,
			true
		);

		if (VelocityFound)
		{
			FVector Normal = SuggestedVelocity.GetSafeNormal();
			MoveBarrelToward(Normal);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Bad Angle %s"), *SuggestedVelocity.ToString());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No barrel attached, cannot aim!"));
	}
}

void UTankAimingComponent::MoveBarrelToward(FVector MoveTo)
{
	// set pitch rotation to the new vector for the barrel
	// set yaw rotation to the new vector for the turret	
	_Barrel->Elevate(5);
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * Barrel)
{
	_Barrel = Barrel;
}
