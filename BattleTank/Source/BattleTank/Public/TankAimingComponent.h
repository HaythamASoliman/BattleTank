// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


//Enum Aiming states
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked,
};


class UTankBarrel; //
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankBarrel* TankBarrel, UTankTurret* TankTurret);

	void AimAt(FVector WorldSpaceAim, float LaunchSpeed);

	UTankBarrel* GetBarrel();

	//void SetBarrel(UTankBarrel* Barrel);

	//void SetTurret(UTankTurret* Turret);

	//todo add setturretRef

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringState FiringState = EFiringState::Aiming;

private:
	UTankBarrel* Barrel;
	UTankTurret* Turret;
	void MoveBarrelTowards(FVector AimDirection);



		
};
