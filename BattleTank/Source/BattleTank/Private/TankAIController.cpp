// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"

DEFINE_LOG_CATEGORY(GeneralLog);

void ATankAIController::BeginPlay()
{
	UE_LOG(GeneralLog, Warning, TEXT("Testing AI on Tank: %s"), *(GetPawn()->GetName()));
}
