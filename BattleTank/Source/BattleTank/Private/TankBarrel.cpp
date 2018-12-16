// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
//#include "Kismet/KismetMathLibrary.h"

void UTankBarrel::Elevate(float ElevationSpeed)
{

	ElevationSpeed = FMath::Clamp(ElevationSpeed, -1.f, 1.f);
	auto ElevationChange = ElevationSpeed * MaxDegreePerSecond * GetWorld()->DeltaTimeSeconds;

	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	RawNewElevation = FMath::Clamp(RawNewElevation, MinElevation, MaxElevation);
	SetRelativeRotation(FRotator(RawNewElevation, 0, 0));
}
