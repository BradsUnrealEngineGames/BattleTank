// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Tank.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/PlayerController.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	APawn* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	APawn* ControlledTank = GetPawn();

	if (PlayerTank)
	{
		MoveToActor(PlayerTank, AcceptanceRadius);

		FVector Target = PlayerTank->FindComponentByClass<UPrimitiveComponent>()->GetComponentLocation();

		ControlledTank->FindComponentByClass<UTankAimingComponent>()->AimAt(Target);
		if (ControlledTank->FindComponentByClass<UTankAimingComponent>()->GetFiringState() == EFiringState::Locked) {
			ControlledTank->FindComponentByClass<UTankAimingComponent>()->Fire();
		}
		
	}
}