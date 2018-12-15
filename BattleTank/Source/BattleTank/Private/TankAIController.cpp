// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "Engine/World.h"

DEFINE_LOG_CATEGORY(GenLog);

void ATankAIController::BeginPlay()
{
	
	//Can

	Super::BeginPlay();

	Tank = GetControlledTank();


	if (Tank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController is possessing tank: %s"), *(Tank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("AIController is not possessing any tank!"));
	}

	PlayerTank = GetPlayerTank();

	if (PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AIController found player tank: %s"), *(PlayerTank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("AIController couldn't find player tank!"));
	}
}

ATank* ATankAIController::GetControlledTank()
{
	return Cast<ATank>(GetPawn());
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PlayerTank = GetPlayerTank();
	//UE_LOG(LogTemp, Warning, TEXT("AI Aiming"));
	if (PlayerTank) {
		GetControlledTank()->AimAt(PlayerTank->GetActorLocation());
	}
}

ATank* ATankAIController::GetPlayerTank() const
{

	UWorld* World = GetWorld();

	if (World) {
		auto PlayerController = World->GetFirstPlayerController();
		if (PlayerController) {
			return Cast<ATank>(PlayerController->GetPawn());
		}
	}

	return nullptr;

}
