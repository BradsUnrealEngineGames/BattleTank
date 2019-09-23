// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::RotateTurret(float RelativeSpeed)
{
	float RelativeSpeedClamped = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	float AzimuthChange = RelativeSpeedClamped * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float NewAzimuth = RelativeRotation.Yaw + AzimuthChange;
	SetRelativeRotation(FRotator(0, NewAzimuth, 0));
}