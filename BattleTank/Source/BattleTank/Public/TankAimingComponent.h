// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8
{
	Locked,
	Aiming,
	Reloading
};

struct ProjectileLaunchLocation
{
	FVector Location;
	FRotator Rotation;
};

class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	
	UFUNCTION(BlueprintCallable, category = "Setup")
		void Initialize(UTankBarrel* Barrel, UTankTurret* Turret);

	void AimAt(FVector TargetLocation, float LaunchSpeed);
	ProjectileLaunchLocation GetLaunchLocation();

protected:
	UPROPERTY(BlueprintReadonly, Category="Setup")
	EFiringStatus FiringStatus = EFiringStatus::Aiming;


private:
	UTankBarrel* _Barrel = nullptr;
	UTankTurret* _Turret = nullptr;
	void MoveBarrelToward(FVector MoveTo);
};
