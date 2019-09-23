// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed) 
{
	float RelativeSpeedClamped = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	float ElevationChange = RelativeSpeedClamped * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	float ClampedElevation = FMath::Clamp(RawNewElevation, 0.f, 40.f);
	SetRelativeRotation(FRotator(ClampedElevation, 0, 0));
}