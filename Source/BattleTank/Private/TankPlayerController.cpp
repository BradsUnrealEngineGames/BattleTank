// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent)) {
		FoundAimingComponent(AimingComponent);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Player controller can't find aiming component at begin play"))
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

APawn* ATankPlayerController::GetControlledTank() const
{
	return GetPawn();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(GetControlledTank())) { 
		UE_LOG(LogTemp, Error, TEXT("TankPlayerController: AimTowardsCrosshair - could not get controlled tank"))
		return; 
	}
	FVector HitLocation;
	if (GetLookVectorHitLocation(HitLocation))
	{
		GetControlledTank()->FindComponentByClass<UTankAimingComponent>()->AimAt(HitLocation);
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