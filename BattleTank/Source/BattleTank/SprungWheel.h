// Copyright Mafara Ltd

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

class USphereComponent;
class UPhysicsConstraintComponent;

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddDrivingForce(float ForceMangnitude);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	void SetupConstraint();

	// Components
	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent* Wheel = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent* Axle = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPhysicsConstraintComponent* MassWheelConstraint = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPhysicsConstraintComponent* AxleWheelConstraint = nullptr;
};
