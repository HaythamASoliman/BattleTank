// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Components/PrimitiveComponent.h"

void UTankTrack::SetThrottle(float Throttle)
{
	//UE_LOG(LogTemp, Warning, TEXT("%s is Throttling at :%f"), *GetName(), Throttle);

	FVector AppliedForce = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	

	UPrimitiveComponent* TankBody = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	//UE_LOG(LogTemp, Warning, TEXT("%s is applying force Throttling af :%s"), *GetName(), *AppliedForce.ToString());
	TankBody->AddForceAtLocation(AppliedForce, GetComponentLocation());
}
