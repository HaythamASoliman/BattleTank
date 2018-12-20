// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"

DEFINE_LOG_CATEGORY(GenLog);

void ATankAIController::BeginPlay()
{
	
	Super::BeginPlay();

}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	auto ControlledTank = GetPawn();


	if (!ensure(PlayerTank && ControlledTank)) return;

	MoveToActor(PlayerTank, AcceptanceRadius); //todo check radius is in cm

	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	//if (!IsParticipating) return;
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	AimingComponent->Fire();
}
