// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "Engine/World.h"

DEFINE_LOG_CATEGORY(GenLog);

void ATankAIController::BeginPlay()
{
	
	Super::BeginPlay();

	ControlledTank = Cast<ATank>(GetPawn());
}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());



	if (PlayerTank && ControlledTank) {

		MoveToActor(PlayerTank, AcceptanceRadius); //todo check radius is in cm

		if (!(ControlledTank->IsParticipating)) return;
		//UE_LOG(LogTemp, Warning, TEXT("MMM: %s"), *GetName());
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		//ControlledTank->Fire(); //todo don't fire every frame;
	}
}
