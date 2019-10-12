// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "GameFramework/Pawn.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/PlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

/* Sets controlled tank. Necessary because BeginPlay race conditions could prevent the OnDeath delegate from adding the function OnPossessedTankDeath*/
void ATankAIController::SetPawn(APawn* InPawn) {
	Super::SetPawn(InPawn);
	if (InPawn) {
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::OnPossessedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Called cpp on possessed tank death"))
	if (GetPawn()) {
		OnPossessedTankDeathBlueprintAI();
		Dead = true;
		GetPawn()->DetachFromControllerPendingDestroy();
		UE_LOG(LogTemp, Warning, TEXT("Found pawn"));
		
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	APawn* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	APawn* ControlledTank = GetPawn();
	if (!Dead) {
		if (PlayerTank)
		{
			if (ensure(ControlledTank)) {
				MoveToActor(PlayerTank, AcceptanceRadius);

				FVector Target = PlayerTank->FindComponentByClass<UPrimitiveComponent>()->GetComponentLocation();

				ControlledTank->FindComponentByClass<UTankAimingComponent>()->AimAt(Target);
				if (ControlledTank->FindComponentByClass<UTankAimingComponent>()->GetFiringState() == EFiringState::Locked) {
					ControlledTank->FindComponentByClass<UTankAimingComponent>()->Fire();
				}
			}
		}
	}
	
}