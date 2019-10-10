// Copyright Bradley Olson

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

class UPhysicsConstraintComponent;
class UStaticMeshComponent;

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "SystemParts")
	UStaticMeshComponent* Mass;

	UPROPERTY(VisibleAnywhere, Category = "SystemParts")
	UStaticMeshComponent* Wheel;

	UPROPERTY(VisibleAnywhere, Category = "SystemParts")
	UPhysicsConstraintComponent* PhysicsConstraint;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
