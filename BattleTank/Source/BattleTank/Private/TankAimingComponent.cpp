// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include <DrawDebugHelpers.h>
#include <Components/ActorComponent.h>
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// Work-out difference between current barrel rotation, and AimDirectoin
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotation = AimDirection.Rotation();
	auto DeltaRotation = AimAsRotation - BarrelRotation;



	// Move the barrel the right amount this frame"
	// Given a max elevation speed,	and the frame time". Because we want to be
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) {
		UE_LOG(LogTemp, Warning, TEXT("Barrel is null for %s"), *(GetOwner()->GetName()));
		return;
	}
	
	UWorld* World = GetWorld();
	if (World) {
		DrawDebugLine(World, GetOwner()->GetTransform().GetLocation(), HitLocation, FColor::Red, false, -1, 0, 12.333);
	}


	FVector OutLaunchVelocity(0);

	FCollisionResponseParams ResponseParam;
	TArray<AActor*> IgnoredActors;
	bool CanReach = 
	UGameplayStatics::SuggestProjectileVelocity(
		GetWorld(),
		OUT OutLaunchVelocity,
		Barrel->GetSocketLocation(FName("Projectile")),
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace,
		ResponseParam,
		IgnoredActors,
		true
		);

	if (CanReach) {
		//FVector LaunchDirection = OutLaunchVelocity.GetSafeNormal();
		//UE_LOG(LogTemp, Warning, TEXT("%s is aiming  at: %s from %s"), *(GetOwner()->GetName()), *((HitLocation).ToString()), *(Barrel->GetComponentLocation().ToString()));
		UE_LOG(LogTemp, Warning, TEXT("%s is firing at Direction: %s"), *(GetOwner()->GetName()), *OutLaunchVelocity.Rotation().ToString());
	
		MoveBarrelTowards(OutLaunchVelocity.GetSafeNormal());



	}

}

void UTankAimingComponent::SetBarrel(UStaticMeshComponent* barrel)
{
	this->Barrel = barrel;
}

