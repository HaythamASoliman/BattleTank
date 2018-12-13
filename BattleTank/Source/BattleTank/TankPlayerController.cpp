// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank()
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
	Tank = Cast<ATank>(GetPawn());

	if (Tank) {
		UE_LOG(LogTemp, Warning, TEXT("%s is the possessed tank!"), *(Tank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No possessed tank found!"));
	}
	
}