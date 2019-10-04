// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay() {
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0;
}

void UTankTrack::ApplySidewaysForce() {
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	// Work-out the required acceleration this frame to correct
	auto CorrectionAcceleration = (-SlippageSpeed / DeltaTime) * GetRightVector();

	// Calculate and apply sideways (F = m a)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2;
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle) {
	CurrentThrottle = FMath::Clamp<float>((CurrentThrottle + Throttle), -1, 1);
}

void UTankTrack::DriveTrack()
{
	FVector ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
;

