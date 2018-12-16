// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))//, hideCategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// -1 is max downward speed, and +1 is max upward speed
	void Elevate(float ElevationSpeed);



private:
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreePerSecond = 5.f;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxElevation = 40.f;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MinElevation = 0.f;
	
};
