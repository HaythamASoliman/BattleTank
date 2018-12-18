// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{

	GENERATED_BODY()
public:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	ATank* GetControlledTank();

protected:
	virtual void Tick(float DeltaSeconds) override;
	
private:

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	ATank* Tank;
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(OUT FVector& HitLocation) const;

	bool GetSightRayHitLocation(FString &ObjectHit, FVector &HitLoc);
	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "0.1", ClampMax = "0.9", UIMin = "0.1", UIMax = "0.0"))
		float CrossHairXLocation = 0.5f;

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "0.1", ClampMax = "0.9", UIMin = "0.1", UIMax = "0.0"))
		float CrossHairYLocation = 0.33333f;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000.f;

	FVector CameraLocation;
};
