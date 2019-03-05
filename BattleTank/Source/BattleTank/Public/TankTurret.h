// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Spin(float RelativeSpeed);

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxDegreesPerSecond = 25;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MinRotationDegrees = -145;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxRotationDegrees = 145;
};
