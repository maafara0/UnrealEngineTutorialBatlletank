// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8 {
	Reloading, 
	Aiming, 
	Locked};

class UTankBarrel;
class UTankTurret;
class AProjectile;
//Holds paremeters for barrel's property and elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable, Category = "InGame")
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	void AimAt(FVector WorldSpaceAimTarget);

	//TODO add set turrent rference

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

private:

	UPROPERTY(EditDefaultsOnly/*Edit on BP file only*/, Category = "Fireing")
	float LaunchSpeed = 4000;

	// Sets default values for this component's properties
	UTankAimingComponent();
	//Barrel
	UTankBarrel* Barrel = nullptr;

	UTankTurret* Turret = nullptr;

	void MoveBarrelTowards(FVector AimDirection);

	//UPROPERTY(EditDefaultsOnly/*Edit on BP file only*/, Category = "Fireing")
	//float LaunchSpeedd = 4000;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlurePrint;

	UPROPERTY(EditAnywhere, Category = "Fireing")
	float ReloadTimeInSeconds = 3;

	//loca barrel reference for projectile
	double LastTimerTime = 0;
};
