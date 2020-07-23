// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	// sets value for elevation change
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = GetRelativeRotation().Pitch + ElevationChange;
	/*void FMath::Clamp()
	{

	}*/
	SetRelativeRotation(FRotator(RawNewElevation, 0, 0));
}