// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

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

	// How close can the AI tank get to the player before stopping
	float AcceptanceRadius = 3000.f;
};
