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
	UE_LOG(LogTemp, Warning, TEXT("player controller beign "))
}
ATank* ATankPlayerController::GetControlledTank() const
{
	UE_LOG(LogTemp, Warning, TEXT("player controller beign play"))
	return Cast<ATank>(GetPawn());
}