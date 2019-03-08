// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "Tank.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrack, UTankTrack* RightTrack)
{
	_LeftTrack = LeftTrack;
	_RightTrack = RightTrack;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (_LeftTrack && _RightTrack)
	{
		UE_LOG(LogTemp, Warning, TEXT("Movement desired: %f"), Throw);
		_LeftTrack->SetThrottle(Throw);
		_RightTrack->SetThrottle(Throw);
	}
}