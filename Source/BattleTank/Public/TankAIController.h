// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class APawn;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	virtual void Tick(float DeltaTime) override;

	void BeginPlay() override;

	virtual void SetPawn(APawn* InPawn) override;

	// How close can the AI tank get to the player before stopping
protected:
	UPROPERTY(EditAnywhere, Category = "Action")
	float AcceptanceRadius = 8000.f;

	UFUNCTION()
	void OnPossessedTankDeath();
};
