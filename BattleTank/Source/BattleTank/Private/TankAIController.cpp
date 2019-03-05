// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "Public/Tank.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return; }

	ATank* Me = Cast<ATank>(GetPawn());
	ATank* Player = Cast<ATank>(PlayerPawn);
	if (Me && Player)
	{
		FVector PlayerLocation = Player->GetActorLocation();
		Me->AimAt(PlayerLocation);
		Me->Fire();
	}
}
