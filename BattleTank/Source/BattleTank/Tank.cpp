// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include <DrawDebugHelpers.h>
#include "Engine/World.h"
#include "TankBarrel.h"
#include "Projectile.h"



// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

}

void ATank::AimAt(FVector HitLocation)
{
	//auto OurTankName = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s is aiming  at: %s"), *OurTankName, *((HitLocation).ToString()));
	//UWorld* World = GetWorld();
	//if (World) {
	//	DrawDebugLine(World, GetTransform().GetLocation(), HitLocation, FColor::Red);
	//}

	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
	
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
//void ATank::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::SetBarrelRef(UTankBarrel* Barrel)
{
	if (!Barrel) {
		UE_LOG(LogTemp, Error, TEXT("Barrel is null in: %s"), *GetName());
		return;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Barrel assined to: %s"), *GetName());
	}
	TankAimingComponent->SetBarrel(Barrel);
	this->Barrel = Barrel;
}

void ATank::SetTurretRef(UTankTurret* Turret)
{
	if (!Turret) {
		UE_LOG(LogTemp, Error, TEXT("Turret is null in: %s"), *GetName());
		return;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Turret assined to: %s"), *GetName());
	}
	TankAimingComponent->SetTurret(Turret);
}

void ATank::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("%s is firing"), *GetName());


	//auto ProjectileSocket = Barrel->GetSo

	GetWorld()->SpawnActor<AProjectile>(ProjectileBP, Barrel->GetSocketLocation("Projectile"), Barrel->GetSocketRotation("Projectile"));
}

