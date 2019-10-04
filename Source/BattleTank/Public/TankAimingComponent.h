// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "TankAimingComponent.generated.h"



// Enum for aiming state
UENUM()
enum class EFiringState : uint8 {
	Reloading,
	Aiming,
	Locked
};

class UTankTurret;
class UTankBarrel;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	UTankTurret* Turret = nullptr;

	void MoveBarrel(FVector AimDirection);

	void MoveTurret(FVector AimDirection);

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	float ReloadTimeInSeconds = 3.f;
	float LastFireTime = -3.f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Aiming;

public:	

	UTankBarrel* Barrel;
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "Action")
	void Fire();

	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 4000.f; // Sensible starting value
};
