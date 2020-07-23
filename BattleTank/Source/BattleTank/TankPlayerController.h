// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

private:

	ATank* GetControlledTank() const;

	//start the tank moving battel so that a shot would hit where the 
	//crosshair intersect the world
	void AimTowardsCrosshair();

	//croshair location
	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5;
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.3333;
	//return an out parameter true if hit landscappe
	bool GetSightRayLocation(FVector &OutHitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.;
};
