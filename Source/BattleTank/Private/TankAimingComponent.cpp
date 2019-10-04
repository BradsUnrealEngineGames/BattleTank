// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Kismet/GameplayStatics.h"
#include "TankTurret.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (GetWorld()->GetTimeSeconds() -LastFireTime > ReloadTimeInSeconds) {
		FiringState = EFiringState::Aiming;
	}
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	// So that first fire is after initial reload
	LastFireTime = FPlatformTime::Seconds();
	Barrel = GetOwner()->FindComponentByClass<UTankBarrel>();
	// ...
	
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet) {
	if (ensure(BarrelToSet && TurretToSet)) {
		Barrel = BarrelToSet;
		Turret = TurretToSet;
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Function Initialize: %s could not find Barrel or Turret"), *GetName());
	}
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	FVector DropHitLocation(0, 0, -400);
	HitLocation = HitLocation + DropHitLocation;
	// Check barrel and turret pointers
	if (!ensure(Barrel)) { 
		UE_LOG(LogTemp, Error, TEXT("Function AimAt: %s could not find Barrel"), *GetName()); 
		return; 
	}
	if (!ensure(Turret)) { 
		UE_LOG(LogTemp, Error, TEXT("Function AimAt: %s could not find Barrel"), *GetName()); 
		return; 
	}
	/// Formulate inputs and call SuggestProjectileVelocity
	FVector OutLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace)) {
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
		MoveTurret(AimDirection);
	}
	else
	{
		MoveBarrel(OutLaunchVelocity);
	}
	
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection) 
{
	/// Work out difference between current barrel rotation, and AimDirection
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotation;
	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurret(FVector AimDirection)
{
	FRotator TurretRotation = Turret->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - TurretRotation;
	Turret->RotateTurret(DeltaRotator.Yaw);
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel)) {
		UE_LOG(LogTemp, Error, TEXT("%s could not find Barrel"), *GetName());
		return;
	}
	if (FiringState == EFiringState::Reloading) { return; }
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileBlueprint,
		Barrel->GetSocketLocation(FName("ProjectileStart")),
		Barrel->GetSocketRotation(FName("ProjectileStart"))
		);
	if (ensure(Projectile)) {
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
		FiringState = EFiringState::Reloading;
	}
}