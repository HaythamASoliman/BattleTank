// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include <DrawDebugHelpers.h>
#include <Components/ActorComponent.h>
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Public/TankBarrel.h"
#include "Public/TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false; //todo should this really tick?

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


UTankBarrel* UTankAimingComponent::GetBarrel()
{
	if (this)
	return this->Barrel;
	return nullptr;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// Work-out difference between current barrel rotation, and AimDirectoin
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto TurretRotation = Turret->GetForwardVector().Rotation();
	auto AimAsRotation = AimDirection.Rotation();
	auto DeltaBarrelRotation = AimAsRotation - BarrelRotation;
	auto DeltaTurretRotation = AimAsRotation - TurretRotation;


	Barrel->Elevate(DeltaBarrelRotation.Pitch);
	Turret->Rotatae(DeltaTurretRotation.Yaw);


	// Move the barrel the right amount this frame"
	// Given a max elevation speed,	and the frame time". Because we want to be
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::Initialise(UTankBarrel* TankBarrel, UTankTurret* TankTurret)
{
	this->Barrel = TankBarrel;
	this->Turret = TankTurret;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel) || !ensure(Turret)) return;


	//return;

	UWorld* World = GetWorld();
	if (World) {
		//DrawDebugLine(World, GetOwner()->GetTransform().GetLocation(), HitLocation, FColor::Red, false, -1, 0, 12.333);

		FVector OutLaunchVelocity(0);
		FVector StartLocation = Barrel->GetComponentLocation();// ->GetSocketLocation(FName("Projectile"));

		//FCollisionResponseParams ResponseParam;
		//TArray<AActor*> IgnoredActors;
		bool CanReach =
			UGameplayStatics::SuggestProjectileVelocity(
				World,
				OUT OutLaunchVelocity,
				StartLocation,
				HitLocation,
				LaunchSpeed,
				false,
				0,
				0,
				ESuggestProjVelocityTraceOption::DoNotTrace
				//,
				//ResponseParam,
				//IgnoredActors,
				//true
			);

		auto Time = World->GetTimeSeconds();

		if (CanReach) {
			//FVector LaunchDirection = OutLaunchVelocity.GetSafeNormal();
			//UE_LOG(LogTemp, Warning, TEXT("%s is aiming  at: %s from %s"), *(GetOwner()->GetName()), *((HitLocation).ToString()), *(Barrel->GetComponentLocation().ToString()));



			//UE_LOG(LogTemp, Warning, TEXT("%f - %s is firing at Direction: %s"), Time, *(GetOwner()->GetName()), *OutLaunchVelocity.Rotation().ToString());

			MoveBarrelTowards(OutLaunchVelocity.GetSafeNormal());


		}
		else {
			//UE_LOG(LogTemp, Warning, TEXT("%f - %s Unreachable Targets to shoot at!"), Time, *(GetOwner()->GetName()));
		}
	}

}


void UTankAimingComponent::Fire()
{
	//UE_LOG(LogTemp, Warning, TEXT("%s is firing"), *GetName());

	bool isReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeInSeconds;

	//auto ProjectileSocket = Barrel->GetSo


	if (ensure(Barrel && ProjectileBlueprint) && isReloaded) {
		LastFireTime = GetWorld()->GetTimeSeconds();
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation("Projectile"), Barrel->GetSocketRotation("Projectile"));

		Projectile->LaunchProjectile(LaunchSpeed);
	}
}

//void UTankAimingComponent::SetBarrel(UTankBarrel* Barrel)
//{
//	this->Barrel = Barrel;
//}
//
//void UTankAimingComponent::SetTurret(UTankTurret* Turret)
//{
//	this->Turret = Turret;
//}

