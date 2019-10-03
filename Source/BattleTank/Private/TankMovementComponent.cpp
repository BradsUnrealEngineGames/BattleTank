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
	UE_LOG(LogTemp, Warning, TEXT("Intend move forward: %f"),Throw);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

// Used with negative values for left turns
void UTankMovementComponent::IntendTurnRight(float Throw) {
	UE_LOG(LogTemp, Warning, TEXT("Intend move forward: %f"), Throw);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}