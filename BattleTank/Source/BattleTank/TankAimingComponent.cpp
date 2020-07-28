// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
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
void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if ((FPlatformTime::Seconds() - LastTimerTime) > ReloadTimeInSeconds)
	{
		FiringState = EFiringState ::Reloading;
	}
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	// first fire is after reload
	LastTimerTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector WorldSpaceAimTarget)
{
	if (!ensure(Barrel)) { return; }

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
		//UE_LOG(LogTemp, Error, TEXT("FAILD To set calculate aim %f"), GetWorld()->GetTimeSeconds())
	}

}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if(ensure(!Barrel || !Turret))
	{
		return;
	}
	// x vector rotation of barrel
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();

	// converts Vector of aim direction to a rotator
	FRotator AimAsRotator = AimDirection.Rotation();

	//difference between barrel rotation and desierd rotation
	auto DletaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DletaRotator.Pitch);
	Turret->Rotate(DletaRotator.Yaw);

}

void UTankAimingComponent::Fire()
{
	bool isReloaded = FPlatformTime::Seconds() - LastTimerTime > ReloadTimeInSeconds;
	if (FiringState != EFiringState::Reloading) {

		//spawn projectile at the socket of projectile
		if (!ensure(Barrel && ProjectileBlurePrint)) { return; }
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlurePrint,
			Barrel->GetSocketLocation("Projectile"),
			Barrel->GetSocketRotation("Projectile"));
		Projectile->LaunchProjectile(LaunchSpeed);

		LastTimerTime = FPlatformTime::Seconds();
	}
}