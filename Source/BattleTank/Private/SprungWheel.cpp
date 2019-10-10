// Copyright Bradley Olson


#include "SprungWheel.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("PhysicsConstraint"));
	SetRootComponent(PhysicsConstraint);

	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->SetupAttachment(PhysicsConstraint);
	this->AddInstanceComponent(Axle);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Axle);
	this->AddInstanceComponent(Wheel);

	AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleWheelConstraint"));
	AxleWheelConstraint->SetupAttachment(Axle);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	SetupConstraint();
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	if (Wheel) {
		Wheel->AddForce(Axle->GetForwardVector() * ForceMagnitude);
	}
}

void ASprungWheel::SetupConstraint() {
	if (!GetAttachParentActor()) { return; }
	UStaticMeshComponent* BodyRoot = Cast<UStaticMeshComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) { return; }
	PhysicsConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Axle, NAME_None);
	AxleWheelConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
}

