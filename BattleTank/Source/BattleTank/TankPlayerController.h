// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{

	GENERATED_BODY()
public:

	virtual void BeginPlay() override;
	ATank* GetControlledTank();

protected:
	virtual void Tick(float DeltaSeconds) override;
	
private:
	ATank* Tank;
	void AimTowardsCrosshair();
};
