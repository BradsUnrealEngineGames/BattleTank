// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = true;
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<USceneComponent*> Children;
	TArray<ASprungWheel*> Wheels;
	GetChildrenComponents(true, Children);
	for (USceneComponent* Child: Children) {
		USpawnPoint* SpawnPoint = Cast<USpawnPoint>(Child);
		if (!SpawnPoint) { continue; }
		ASprungWheel* ChildWheel = Cast<ASprungWheel>(SpawnPoint->GetSpawnedActor());
		if (!ChildWheel) { continue; }
		Wheels.Add(ChildWheel);
	}
	return Wheels;
}

void UTankTrack::SetThrottle(float Throttle) {
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	float ForceApplied = CurrentThrottle * TrackMaxDrivingForce;
	TArray<ASprungWheel*> Wheels = GetWheels();
	float ForcePerWheel = ForceApplied / Wheels.Num();
	for (ASprungWheel* Wheel : Wheels) {
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}
;

