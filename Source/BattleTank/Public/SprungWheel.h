// Copyright Bradley Olson

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

class UPhysicsConstraintComponent;
class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
private:
	void SetupConstraint();

	void ApplyForce();

	float TotalForceMagnitudeThisFrame = 0;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "SystemParts")
	USphereComponent* Wheel =  nullptr;
	UPROPERTY(VisibleAnywhere, Category = "SystemParts")
	USphereComponent* Axle = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "SystemParts")
	UPhysicsConstraintComponent* PhysicsConstraint = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "SystemParts")
	UPhysicsConstraintComponent* AxleWheelConstraint = nullptr;

public:	
	// Sets default values for this actor's properties
	ASprungWheel();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddDrivingForce(float ForceMagnitude);
};
