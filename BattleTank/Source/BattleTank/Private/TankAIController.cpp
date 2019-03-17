// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "Public/Tank.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!ensure(PlayerPawn)) { return; }

	ATank* Me = Cast<ATank>(GetPawn());
	ATank* Player = Cast<ATank>(PlayerPawn);
	if (!ensure(Me)) { return; }

	UTankAimingComponent* AimingComp = Me->FindComponentByClass<UTankAimingComponent>();
	if (ensure(Me && Player && AimingComp))
	{
		MoveToActor(Player, 10);

		FVector PlayerLocation = Player->GetActorLocation();
		AimingComp->AimAt(PlayerLocation);
		AimingComp->Fire();
	}
}
