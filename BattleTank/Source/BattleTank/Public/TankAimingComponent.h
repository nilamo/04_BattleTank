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
	Reloading,
	OutOfAmmo
};

struct ProjectileLaunchLocation
{
	FVector Location;
	FRotator Rotation;
};

class AProjectile;
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

	UFUNCTION(BlueprintCallable, category="Firing")
	void AimAt(FVector TargetLocation);

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 8000;

	UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire();

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBP;

	EFiringStatus GetFiringState() const;

protected:
	UPROPERTY(BlueprintReadonly, Category="Setup")
	EFiringStatus FiringStatus = EFiringStatus::Reloading;

	UFUNCTION(BlueprintCallable, Category = "Firing")
		int32 RemainingAmmo() const;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		int32 CurrentAmmo = 3;

private:
	void BeginPlay() override;
	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UTankBarrel* _Barrel = nullptr;
	UTankTurret* _Turret = nullptr;
	void MoveBarrelToward(FVector MoveTo);
	bool IsBarrelMoving();
	FVector CurrentlyAimingTo = FVector::ZeroVector;

	float TimeToReload = 3.0f;
	double LastFireTime = 0;

	ProjectileLaunchLocation GetLaunchLocation();
};
