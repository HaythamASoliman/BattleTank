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

protected:
	virtual void Tick(float DeltaTime) override;

private:
	ATank* Tank;
	ATank* PlayerTank;
	ATank* GetPlayerTank() const;
	ATank* GetControlledTank();
};
