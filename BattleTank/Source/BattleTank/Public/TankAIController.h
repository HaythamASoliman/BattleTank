// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(GenLog, Log, All);

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	//UPROPERTY(EditAnywhere, Category = Action)
	//	bool IsParticipating = true;

protected:
	virtual void Tick(float DeltaTime) override;

private:
	//ATank* ControlledTank;
	//ATank* PlayerTank;

	//How close can the AI tank get.
	UPROPERTY(EditAnywhere)
	float AcceptanceRadius = 3000.f;
};
