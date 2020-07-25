// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	//Throttle = FMath::Clamp<float>(Throttle, 0, 1);
	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%S Throttle value: %f"), *Name, Throttle)

	auto ForceApllied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApllied, ForceLocation);

}