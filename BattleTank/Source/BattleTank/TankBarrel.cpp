// Fill out your copyright notice in the Description page of Project Settings.


//#include "Math/UnrealMathUtility.h"
#include "TankBarrel.h"
void UTankBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1,1); // set min\max for input
	
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = GetRelativeRotation().Pitch + ElevationChange;

	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegree, MaxElevationDegree); // set degree limitations
	SetRelativeRotation(FRotator(Elevation, 0, 0));
}