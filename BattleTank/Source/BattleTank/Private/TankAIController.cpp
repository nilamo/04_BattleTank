// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "Public/Tank.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::BeginPlay()
{
	ATank* Tank = GetPlayerTank();
	if (Tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Tank Found: %s"), *(Tank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Tank not found"));
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	APawn* Pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!Pawn) { return nullptr; }
	return Cast<ATank>(Pawn);
}
