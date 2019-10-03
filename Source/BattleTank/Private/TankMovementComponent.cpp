// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::InitializeComponent(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {
	if (LeftTrackToSet && RightTrackToSet) {
		LeftTrack = LeftTrackToSet;
		RightTrack = RightTrackToSet;
	}
}

// Used with negative values for backward acceleration
void UTankMovementComponent::IntendMoveForward(float Throw) {
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

// Used with negative values for left turns
void UTankMovementComponent::IntendTurnRight(float Throw) {
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();

	float Dot = FVector::DotProduct(TankForward, AIForwardIntention);

	IntendMoveForward(Dot);
}
