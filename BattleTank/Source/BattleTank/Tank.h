// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class AProjectile;
UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "InGame")
	void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlurePrint;

	UPROPERTY(EditDefaultsOnly/*Edit on BP file only*/, Category = "Fireing")
	float LaunchSpeed = 4000;

	UPROPERTY(EditAnywhere, Category = "Fireing")
	float ReloadTimeInSeconds = 3;

	//loca barrel reference for projectile
	UTankBarrel* Barrel = nullptr;
	double LastTimerTime = 0;
};
