// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void AimAt(FVector HitLocation);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetBarrelRef(UTankBarrel* barrel);

protected:
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	UTankAimingComponent* TankAimingComponent = nullptr;


private:	
	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 200000.f; //TODO find sensible default value ex:1000 m/s
	
};
