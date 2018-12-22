// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Components/PrimitiveComponent.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	//UE_LOG(LogTemp, Warning, TEXT("I'm hit, I'm hit!"));

	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0;
}

void UTankTrack::SetThrottle(float Throttle)
{
	//UE_LOG(LogTemp, Warning, TEXT("%s is Throttling at :%f"), *GetName(), Throttle);
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);


}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//UE_LOG(LogTemp, Warning, TEXT("%s is Ticking"), *GetName());

}

void UTankTrack::ApplySidewaysForce()
{
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	// Work-out the required acceleration this frame to correct
	auto CorrectionAcceleration = -SlippageSpeed / GetWorld()->GetDeltaSeconds() * GetRightVector();

	// Calculate and apply sideways (F = m a)
	UStaticMeshComponent* TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // two tracks
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::DriveTrack()
{

	FVector AppliedForce = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;


	UPrimitiveComponent* TankBody = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	UE_LOG(LogTemp, Warning, TEXT("%s is applying force Throttling as :%s"), *GetName(), *AppliedForce.ToString());
	TankBody->AddForceAtLocation(AppliedForce, GetComponentLocation());
}