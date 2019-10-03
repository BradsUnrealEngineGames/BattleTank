// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

private:
	UTankTrack* LeftTrack = nullptr;

	UTankTrack* RightTrack = nullptr;
public:
	UFUNCTION(BlueprintCallable, Category = Action)
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = Action)
	void IntendTurnRight(float Throw);
	
	UFUNCTION(BlueprintCallable, Category = Setup)
	void InitializeComponent(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);
};
