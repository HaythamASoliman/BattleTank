// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::Rotatae(float RotationSpeed)
{
	RotationSpeed = FMath::Clamp(RotationSpeed, -1.f, 1.f);
	auto RotationChange = RotationSpeed * MaxDegreePerSecond * GetWorld()->DeltaTimeSeconds;

	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;
	//RawNewElevation = FMath::Clamp(RawNewElevation, MinElevation, MaxElevation);
	SetRelativeRotation(FRotator(0, RawNewRotation, 0));
}
