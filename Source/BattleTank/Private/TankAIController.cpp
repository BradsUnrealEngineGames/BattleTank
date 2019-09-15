// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "TankPlayerController.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	if (GetPlayerTank())
	{
		UE_LOG(LogTemp, Warning, TEXT("Found player controlled tank: %s"), *GetName(),*GetPlayerTank()->GetName())
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No player controlled tank found!"), *GetName())
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