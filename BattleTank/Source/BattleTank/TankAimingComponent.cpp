// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "CollisionQueryParams.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector WorldSpaceAimTarget, float LaunchSpeed)
{
	if (!Barrel) { return; }

	FVector OutLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
	this,
	OutLaunchVelocity,
	StartLocation,
	WorldSpaceAimTarget,
	LaunchSpeed,
	false,
	0,
	0,
	ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if(bHaveAimSolution)
	{
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal(); 
		MoveBarrelTowards(AimDirection);
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: aim solution found"), Time)
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("FAILD"))
	}

}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// x vector rotation of barrel
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();

	// converts Vector of aim direction to a rotator
	FRotator AimAsRotator = AimDirection.Rotation();

	//difference between barrel rotation and desierd rotation
	auto DletaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(1); // TODO remove magic number

}