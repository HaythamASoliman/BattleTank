// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
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
//class AProjectile;

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

	//void AimAt(FVector WorldSpaceAim, float LaunchSpeed);
	void AimAt(FVector HitLocation);

	EFiringState GetFiringState() const;

	UTankBarrel* GetBarrel();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;
	//void SetBarrel(UTankBarrel* Barrel);

	//void SetTurret(UTankTurret* Turret);

	//todo add setturretRef
	UFUNCTION(BlueprintCallable, Category = Fire)
		void Fire();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringState FiringState = EFiringState::Reloading;

private:
	UTankBarrel* Barrel;
	UTankTurret* Turret;
	void MoveBarrelTowardsAim();
	FVector AimDirection;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 4000.f; //TODO find sensible default value ex:1000 m/s

	//UPROPERTY(EditDefaultsOnly, Category = Firing)
	//	float LaunchSpeed = 4000.f; //TODO find sensible default value ex:1000 m/s

	//	//local usage;
	//UTankBarrel* Barrel = nullptr;

	double LastFireTime = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSeconds = 3;
		
	bool IsBarrelMoving();
};
