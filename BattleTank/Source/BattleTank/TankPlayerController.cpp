// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank()
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	ATank* PlayerTank = GetControlledTank();
	if (!PlayerTank) return;
	//throw std::logic_error("The method or operation is not implemented.");
}

void ATankPlayerController::BeginPlay()
{
	Tank = GetControlledTank();

	if (Tank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController is possessing tank: %s"), *(Tank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("PlayerController is not possessing any tank!"));
	}
	
}