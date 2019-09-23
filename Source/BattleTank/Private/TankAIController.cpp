// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Tank.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank())
	{
		FVector Target = GetPlayerTank()->FindComponentByClass<UPrimitiveComponent>()->GetComponentLocation();
		GetControlledTank()->AimAt(Target);
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) {return nullptr;}
	return Cast<ATank>(PlayerPawn);
}