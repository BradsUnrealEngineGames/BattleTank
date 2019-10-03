// Copyright Bradley Olson

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

	// Called from the pathfinding logic by the AI controller in Nav Movement Component
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
public:
	UFUNCTION(BlueprintCallable, Category = "Action")
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Action")
	void IntendTurnRight(float Throw);
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void InitializeComponent(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);
};
