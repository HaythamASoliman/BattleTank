// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include <DrawDebugHelpers.h>
#include "Engine/World.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include <Kismet/GameplayStatics.h>
#include <GameFramework/Actor.h>



// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UE_LOG(LogTemp, Warning, TEXT( "MMM: Constructor Tank_CPP"));
	//TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	//TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Tank Movement"));

}

void ATank::AimAt(FVector HitLocation)
{
	if (ensure(TankAimingComponent)) {
		TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
	}
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("MMM: BeginPlay BEFORE super Tank_CPP"));
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("MMM: BeginPlay AFTER super Tank_CPP"));
}


// Called to bind functionality to input
//void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//}

//void ATank::SetBarrelRef(UTankBarrel* Barrel)
//{
//	if (!Barrel) {
//		UE_LOG(LogTemp, Error, TEXT("Barrel is null in: %s"), *GetName());
//		return;
//	}
//	else {
//		UE_LOG(LogTemp, Warning, TEXT("Barrel assined to: %s"), *GetName());
//	}
//	TankAimingComponent->SetBarrel(Barrel);
//	//this->Barrel = Barrel;
//}
//
//void ATank::SetTurretRef(UTankTurret* Turret)
//{
//	if (!Turret) {
//		UE_LOG(LogTemp, Error, TEXT("Turret is null in: %s"), *GetName());
//		return;
//	}
//	else {
//		UE_LOG(LogTemp, Warning, TEXT("Turret assigned to: %s"), *GetName());
//	}
//	TankAimingComponent->SetTurret(Turret);
//}

void ATank::Fire()
{
	//UE_LOG(LogTemp, Warning, TEXT("%s is firing"), *GetName());

	bool isReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeInSeconds;

	//auto ProjectileSocket = Barrel->GetSo


	if (ensure(TankAimingComponent->GetBarrel()) && isReloaded) {
		LastFireTime = GetWorld()->GetTimeSeconds();
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBP, TankAimingComponent->GetBarrel()->GetSocketLocation("Projectile"), TankAimingComponent->GetBarrel()->GetSocketRotation("Projectile"));

		Projectile->LaunchProjectile(LaunchSpeed);
	}
}

