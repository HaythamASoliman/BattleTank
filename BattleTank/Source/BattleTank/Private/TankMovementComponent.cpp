// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrack, UTankTrack* RightTrack) {


	this->LeftTrack = LeftTrack;
	this->RightTrack = RightTrack;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) {
		return;
	}

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

	//todo prevent double speed due to double input from MoveForward and TrackInput
	//UE_LOG(LogTemp, Warning, TEXT("%s Intend move forward throw: %f"), *GetName(), Throw);

}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) {
		return;
	}

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);

	//todo prevent double speed due to double input from MoveForward and TrackInput
	//UE_LOG(LogTemp, Warning, TEXT("%s Intend move forward throw: %f"), *GetName(), Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();
	FVector TankForward = GetOwner()->GetActorForwardVector();

	float ForwardThrow = FVector::DotProduct(AIForwardIntention, TankForward);

	IntendMoveForward(ForwardThrow * 0.5f);

	//FVector RightThrow = FVector::CrossProduct(AIForwardIntention, TankForward);
	FVector RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention);

	IntendTurnRight(RightThrow.Z);

	UE_LOG(LogTemp, Warning, TEXT("%s Moving in direction: %s"), *GetOwner()->GetName(), *MoveVelocity.ToString());
}

