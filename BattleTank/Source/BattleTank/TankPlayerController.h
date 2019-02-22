// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Public/Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

#define OUT

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()


private:
	void BeginPlay() override;
	void Tick(float) override;

	ATank* GetControlledTank() const;
	void AimTowardsCursor();
	bool GetSightRayHitLocation(FVector&) const;
	bool GetLookDirection(FVector2D, FVector&) const;
	bool GetLookVectorHitLocation(FVector, FVector&) const;

	UPROPERTY(EditAnywhere)
		float CrosshairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
		float CrosshairYLocation = 1 / 3.0;

	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000;
};
