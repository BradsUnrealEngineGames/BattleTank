// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "Tank.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = Cast<ATank>(GetPawn())->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent)) {
		FoundAimingComponent(AimingComponent);
	}
}

/* Sets controlled tank. Necessary because BeginPlay race conditions could prevent the OnDeath delegate from adding the function OnPossessedTankDeath*/
void ATankPlayerController::SetPawn(APawn* InPawn) {
	Super::SetPawn(InPawn);
	if (InPawn) {
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
	}
}


void ATankPlayerController::OnPossessedTankDeath()
{
	StartSpectatingOnly();
	OnPossessedTankDeathBlueprint();
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
if (!GetControlledTank()) { 
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController: AimTowardsCrosshair - could not get controlled tank"))
		return; 
	}
	FVector HitLocation;
	bool bGotHitLocation = GetLookVectorHitLocation(HitLocation);
	if (bGotHitLocation)
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
	bool DidHit = GetWorld()->LineTraceSingleByChannel(OutHit, StartLocation, StartLocation + (LookDirection* LineTraceRange), ECollisionChannel::ECC_Camera);
	OutHitLocation = OutHit.Location;
	return DidHit;
}