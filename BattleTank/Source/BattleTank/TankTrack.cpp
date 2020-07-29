// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
	//OnComponentHit();
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpluse, const FHitResult& Hit)
{
	//Deive the tracks
	ApplySidewaysForce();
	DriveTrack();
	CurrentThrottle = 0;
	//Apply sidways force
}

void UTankTrack::ApplySidewaysForce()
{
	//slippage speed
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	//required accelerartion
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	//apply sideways friction
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2;
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{

	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
	//DriveTrack();
}

void UTankTrack::DriveTrack()
{
	//Throttle = FMath::Clamp<float>(Throttle, 0, 1);
	auto ForceApllied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApllied, ForceLocation);
}