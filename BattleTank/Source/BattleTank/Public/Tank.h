// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class AProjectile;
class UTankAimingComponent;
class UTankTurret;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeathEvent);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure)
		float GetHealthPercent() const;

	FDeathEvent OnDeathEvent;

protected:
	UPROPERTY(EditDefaultsOnly)
		int32 MaxHealth = 100;

private:
		int32 CurrentHealth = 0;

};
