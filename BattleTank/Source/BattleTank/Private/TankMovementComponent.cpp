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
		_LeftTrack->SetThrottle(Throw);
		_RightTrack->SetThrottle(Throw);
	}
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (_LeftTrack && _RightTrack)
	{
		_LeftTrack->SetThrottle(Throw);
		_RightTrack->SetThrottle(-Throw);
	}
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	auto Forward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto MoveDirection = MoveVelocity.GetSafeNormal();
	auto ForwardMovement = FVector::DotProduct(Forward, MoveDirection);
	auto TurningMovement = FVector::CrossProduct(Forward, MoveDirection);
	UE_LOG(LogTemp, Warning, TEXT("Forward: %f, Turn: %s"), ForwardMovement, *TurningMovement.ToString());
	IntendMoveForward(ForwardMovement);
	IntendTurnRight(TurningMovement.Z);
} 
