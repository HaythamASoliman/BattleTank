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

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

}

void ATank::AimAt(FVector HitLocation)
{
	//auto OurTankName = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s is aiming  at: %s"), *GetName(), *((HitLocation).ToString()));
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

	//float val = 20;
	//val = FMath::Clamp(val, -1.0f, +1.0f);
	//UE_LOG(LogTemp, Warning, TEXT("FPlatformTime: %f"), FPlatformTime::Seconds());
	//UE_LOG(LogTemp, Warning, TEXT("GetWorld: %f"), GetWorld()->GetTimeSeconds());
	//UE_LOG(LogTemp, Warning, TEXT("------------------"));
}

// Called every frame
//void ATank::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//	if (Cast<ATank>(UGameplayStatics::GetPlayerController(this, 0)->GetPawn()) == this) {
//		UE_LOG(LogTemp, Warning, TEXT("FPlatformTime: %f"), FPlatformTime::Seconds());
//		UE_LOG(LogTemp, Warning, TEXT("GetWorld: %f"), GetWorld()->GetTimeSeconds());
//		UE_LOG(LogTemp, Warning, TEXT("%s ------------------"), *GetName());
//	}
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
	//UE_LOG(LogTemp, Warning, TEXT("%s is firing"), *GetName());

	bool isReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeInSeconds;

	//auto ProjectileSocket = Barrel->GetSo


	if (Barrel && isReloaded) {
		LastFireTime = GetWorld()->GetTimeSeconds();
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBP, Barrel->GetSocketLocation("Projectile"), Barrel->GetSocketRotation("Projectile"));

		Projectile->LaunchProjectile(LaunchSpeed);
	}
}

