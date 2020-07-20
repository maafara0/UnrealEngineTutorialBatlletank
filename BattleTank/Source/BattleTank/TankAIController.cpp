// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController can't find player tank tank"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController found player %s"), *PlayerTank->GetName())
	}
	
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank()) {
		FVector PlayerOneLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

		// TODO move towards the player

		//Aim towards the player
		GetControlledTank()->AimAt(PlayerOneLocation);
	}
}


ATank* ATankAIController::GetControlledTank() const
{
		return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}