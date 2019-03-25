// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Engine/World.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	const int32 HealthAdjustment = FMath::Clamp((int32)DamageAmount, 0, CurrentHealth);
	CurrentHealth -= HealthAdjustment;

	if (CurrentHealth <= 0)
	{
		OnDeathEvent.Broadcast();
	}

	UE_LOG(LogTemp, Warning, TEXT("%f: %s took %i damage, and has %i remaining"), GetWorld()->GetTimeSeconds(), *GetName(), HealthAdjustment, CurrentHealth);
	return HealthAdjustment;
}

float ATank::GetHealthPercent() const
{
	return static_cast<float>(CurrentHealth) / static_cast<float>(MaxHealth);
}