// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankMovementComponent.h"
#include "TankAimingComponent.h"
#define UFUNCTION

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	UE_LOG(LogTemp, Error, TEXT("Bom: Tank.cpp CON %s"), *GetName())
}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Error, TEXT("Bom: Tank.cpp"))
	
}

void ATank::AimAt(FVector HitLocation)
{
	if (!TankAimingComponent)
		return;
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	bool isReloaded = FPlatformTime::Seconds() - LastTimerTime > ReloadTimeInSeconds;
	if (Barrel && isReloaded) {

		//spawn projectile at the socket of projectile
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlurePrint,
			Barrel->GetSocketLocation("Projectile"),
			Barrel->GetSocketRotation("Projectile"));
		Projectile->LaunchProjectile(LaunchSpeed);

		LastTimerTime = FPlatformTime::Seconds();
	}
}