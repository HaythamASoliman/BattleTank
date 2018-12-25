// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include <DrawDebugHelpers.h>


//ATank* ATankPlayerController::GetControlledTank()
//{
//	return Cast<ATank>(GetPawn());
//}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

		UTankAimingComponent* AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
		if (!ensure(AimingComponent)) return;

		FoundAimingComponent(AimingComponent);



}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//if (this) {
		AimTowardsCrosshair();
	//}
}

void ATankPlayerController::AimTowardsCrosshair()
{
	auto Pawn = GetPawn();
	if (!Pawn) return; // is u ded?
	UTankAimingComponent* AimingComponent = Pawn->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) return;
	

	FVector HitLocation = FVector::ZeroVector;// = FVector.ZeroVector; //out Param
	CameraLocation = PlayerCameraManager->GetCameraLocation();

	if (GetSightRayHitLocation(OUT HitLocation)) {

		AimingComponent->AimAt(HitLocation);

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


		const AActor* ActorToIgnore = nullptr;

		//	UE_LOG(QuickStart, Log, TEXT("ARayTracing: TraceStart [%f, %f, %f]"), TraceStart.X, TraceStart.Y, TraceStart.Z);
		//	UE_LOG(QuickStart, Log, TEXT("ARayTracing: TraceEnd [%f, %f, %f]"), TraceEnd.X, TraceEnd.Y, TraceEnd.Z);

		FCollisionQueryParams TraceParams(FName(TEXT("RayTracing")), true, ActorToIgnore);
		TraceParams.bReturnPhysicalMaterial = false;
		TraceParams.bTraceComplex = true;


		if (GetWorld()->LineTraceSingleByChannel(OUT HitResult, CameraLocation, CameraLocation + (LookDirection * LineTraceRange), ECollisionChannel::ECC_Visibility, TraceParams)) {
			//UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *(HitResult.Location.ToString()));

			HitLocation = HitResult.Location;

			//DrawDebugLine(GetWorld(), CameraLocation, CameraLocation + (LookDirection * LineTraceRange), FColor::Red);
			DrawDebugLine(GetWorld(), HitResult.TraceStart, HitResult.TraceEnd, FColor::Cyan);

		}
		return true;
	}
	return false;

	
}

//Easier way to do it from lecture discussion
bool ATankPlayerController::GetSightRayHitLocation(FString &ObjectHit, FVector &HitLoc)
{
	// Viewport Size
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	bool bHit;
	FVector2D CrosshairPosition = FVector2D(ViewportSizeX / 2, ViewportSizeY / 3);
	FHitResult HitResult;

	bHit = GetHitResultAtScreenPosition(CrosshairPosition, ECollisionChannel::ECC_WorldStatic, false, HitResult);

	if (bHit)
	{
		HitLoc = HitResult.ImpactPoint;
		ObjectHit = HitResult.GetActor()->GetName();
	}

	// Draws a red line for debugging purposes
	DrawDebugLine(GetWorld(), HitResult.TraceStart, HitResult.TraceEnd, FColor::Red);

	return bHit;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {

	FVector WorldLocation;

	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, OUT WorldLocation, OUT LookDirection)) {
		
		//UE_LOG(LogTemp, Warning, TEXT("World Direction: %s"), *(LookDirection.ToString()));
		return true;
	}


	return false;
}
