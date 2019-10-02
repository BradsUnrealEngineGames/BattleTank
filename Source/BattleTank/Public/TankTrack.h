// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 *	TankTrack is used to set maximum driving force, and to apply forces to the tank
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
private:
	// Max force per track in newtons
	UPROPERTY(EditAnywhere)
	float TrackMaxDrivingForce = 400000;
protected:

public:
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);
};
