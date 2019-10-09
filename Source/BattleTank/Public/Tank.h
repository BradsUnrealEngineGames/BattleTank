// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

private:

	// Sets default values for this pawn's properties
	ATank();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	int32 CurrentHealth;

protected:
	UPROPERTY(EditAnywhere)
	int32 StartingHealth = 100;

public:
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;
};
