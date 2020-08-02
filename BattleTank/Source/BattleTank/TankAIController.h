// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
public:
	void virtual BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//virtual void DetachFromControllerPendingDestroy();
protected:

	UPROPERTY(EditAnywhere, Category = "Setup")
	float AcceptanceRadious = 8000;

	//AI fire when locked bool
	UPROPERTY(EditAnywhere, Category = "Fireing")
	bool bFireOnLock = true;

private:

	virtual void SetPawn(APawn* InPawn) override;
	UFUNCTION()
	void OnDeathCalled();

};
