// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed) 
{
	float RelativeSpeedClamped = FMath::Clamp(RelativeSpeed, 0.f, 1.f);
	float ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	float ClampedElevation = FMath::Clamp(RawNewElevation, 0.f, 40.f);
	SetRelativeRotation(FRotator(ClampedElevation, 0, 0));
}