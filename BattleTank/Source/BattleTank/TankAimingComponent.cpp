// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "CollisionQueryParams.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	if (!BarrelToSet) {
		UE_LOG(LogTemp, Error, TEXT("Barrel not found")) return;
	}
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	if (!TurretToSet) {
		UE_LOG(LogTemp, Error, TEXT("Turret not found")) return;
	}
	Turret = TurretToSet;
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
		//MoveTurretTowards(AimDirection);
		auto Time = GetWorld()->GetTimeSeconds();
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("FAILD To set calculate aim %f"), GetWorld()->GetTimeSeconds())
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

	Barrel->Elevate(DletaRotator.Pitch);
	Turret->Rotate(DletaRotator.Yaw);

}

//void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
//{
//	// x vector rotation of Turret
//	FRotator TurretRotator = Turret->GetUpVector().Rotation();
//
//	// converts Vector of aim direction to a rotator
//	FRotator AimAsRotator = AimDirection.Rotation();
//
//	//difference between Turret rotation and desierd rotation
//	auto DletaRotator = AimAsRotator - TurretRotator;
//
//	Turret->Rotate(DletaRotator.Yaw);
//
//}