// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "Engine/World.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank* ControlledTank = GetControlledTank();
	if (!ControlledTank) 
	{ 
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possesing a tank"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controlling: %s"), *ControlledTank->GetName())
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }
	FVector HitLocation;
	if (GetLookVectorHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& OutHitLocation) const
{
	/// Find crosshair position in screen coordinates
	int32 ViewportSizeX;
	int32 ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	/// De-project screen position into world space coordinates
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) 
	{
		/// Line trace along world space vector to find location
		FVector HitLocation;
		if (GetLookVectorHitLocation(LineTraceRange, LookDirection, HitLocation))
		{
			OutHitLocation = HitLocation;
			return true;
		}

	}
	OutHitLocation = FVector(0.0);
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(float LineTraceRange, FVector LookDirection, FVector& OutHitLocation) const
{
	FHitResult OutHit;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	bool DidHit = GetWorld()->LineTraceSingleByChannel(OutHit, StartLocation, StartLocation + (LookDirection* LineTraceRange), ECollisionChannel::ECC_Visibility);
	OutHitLocation = OutHit.Location;
	return DidHit;
}