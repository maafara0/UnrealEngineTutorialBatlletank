// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "AIController.h"
#include "TankAimingComponent.h"
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) { return; }

	MoveToActor(PlayerTank, AcceptanceRadious);

	//Aim towards the player
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	//Fire when locked
	if (bFireOnLock) {
		if (AimingComponent->GetFiringState() == EFiringState::Locked) {
			AimingComponent->Fire();
		}
	}
	else {
		AimingComponent->Fire();
	}
}