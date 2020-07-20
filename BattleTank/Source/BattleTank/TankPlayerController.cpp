// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Not possesing a tank"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("player controller possesing %s"), *ControlledTank->GetName())
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();

}
	
ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // out perameter
	if (GetSightRayLocation(HitLocation)) // line trace
	{
		GetControlledTank()->AimAt(HitLocation);
			//TODO Tell controlled tank to aim at this pointB
	}
}

//get world location lintrace through crosshair, trug if hits landscape
bool ATankPlayerController::GetSightRayLocation(FVector &OutHitLocation) const
{
	//Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation,ViewportSizeY * CrossHairYLocation);

	//de project the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		//line trace along that look direction and see what we hit up to max range
		GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}

	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + LookDirection * LineTraceRange;

	//line trace along that look direction and see what we hit up to max range
	if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility
			)) 
	{
		OutHitLocation = HitResult.Location;
		return true;
	}
	OutHitLocation = FVector(0);
	return false;
	
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const
{

	FVector CameraWorldLocation; //To be discarded

	return DeprojectScreenPositionToWorld
	(ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		OutLookDirection);

		//UE_LOG(LogTemp, Warning, TEXT("Look Direction %s"), *OutLookDirection.ToString())
}
