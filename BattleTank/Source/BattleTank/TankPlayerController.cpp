// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include <DrawDebugHelpers.h>


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
	

	FVector HitLocation = FVector::ZeroVector;// = FVector.ZeroVector; //out Param
	CameraLocation = PlayerCameraManager->GetCameraLocation();

	if (GetSightRayHitLocation(OUT HitLocation)) {

		//DrawDebugLine(GetWorld(), CameraLocation, HitLocation - CameraLocation, FColor::Red);
		//DrawDebugLine(GetWorld(), HitResult.TraceStart, HitResult.TraceEnd, FColor::Red);
		//UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *((HitLocation - CameraLocation).ToString()));
		//DrawDebugLine(GetWorld(), CameraLocation, HitLocation, FColor::Red);

		GetControlledTank()->AimAt(HitLocation);


	}

	//UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *(HitLocation.ToString()));
}

bool ATankPlayerController::GetSightRayHitLocation(OUT FVector& HitLocation) const
{
	//todo implement cursor hit
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	
	


	//UE_LOG(LogTemp, Warning, TEXT("Cross hair location: %s"), *(ScreenLocation.ToString()));
	FVector LookDirection;
	
	/** We can also set the CameraLocation more accurately using the below code but for saving extra calculation I decided to go with the 
	WorldLocation calculated by DeprojectScreenPositionToWorld
	*/



	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		FHitResult HitResult;

		if (GetWorld()->LineTraceSingleByChannel(OUT HitResult, CameraLocation, CameraLocation + (LookDirection * LineTraceRange), ECollisionChannel::ECC_Visibility)) {
			//UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *(HitResult.Location.ToString()));

			HitLocation = HitResult.Location;

			//DrawDebugLine(GetWorld(), CameraLocation, CameraLocation + (LookDirection * LineTraceRange), FColor::Red);
			//DrawDebugLine(GetWorld(), HitResult.TraceStart, HitResult.TraceEnd, FColor::Cyan);

		}
		return true;
	}
	return false;

	
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {

	FVector WorldLocation;

	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, OUT WorldLocation, OUT LookDirection)) {
		
		//UE_LOG(LogTemp, Warning, TEXT("World Direction: %s"), *(LookDirection.ToString()));
		return true;
	}


	return false;
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	Tank = GetControlledTank();

	if (Tank) {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController is possessing tank: %s"), *(Tank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("PlayerController is not possessing any tank!"));
	}
	
}