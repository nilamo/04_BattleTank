// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::SetThrottle(float Velocity)
{
	UE_LOG(LogTemp, Warning, TEXT("Right track: %f"), Velocity);

	FVector ForceApplied = Velocity * TrackMaxDrivingForce * GetForwardVector();
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}