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
	auto Forward = GetOwner()->GetActorForwardVector();
	auto Diff = (Forward - MoveVelocity).GetSafeNormal();
	IntendMoveForward(Diff.X + Diff.Y);
	IntendTurnRight(Diff.Y);
	UE_LOG(LogTemp, Warning, TEXT("Pathfinding movement request: %s to %s"), *GetOwner()->GetName(), *MoveVelocity.ToString());
}
