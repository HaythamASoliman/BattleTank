// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrack, UTankTrack* RightTrack) {

	if (!LeftTrack || !RightTrack) {
		return;
	}

	this->LeftTrack = LeftTrack;
	this->RightTrack = RightTrack;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

	//todo prevent double speed due to double input from MoveForward and TrackInput
	//UE_LOG(LogTemp, Warning, TEXT("%s Intend move forward throw: %f"), *GetName(), Throw);

}

void UTankMovementComponent::IntendTurnRight(float Throw)
{

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);

	//todo prevent double speed due to double input from MoveForward and TrackInput
	//UE_LOG(LogTemp, Warning, TEXT("%s Intend move forward throw: %f"), *GetName(), Throw);
}
