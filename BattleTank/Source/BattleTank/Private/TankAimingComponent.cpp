// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include <DrawDebugHelpers.h>
#include <Components/ActorComponent.h>
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!Barrel) {
		UE_LOG(LogTemp, Warning, TEXT("Barrel is null for %s"), *(GetOwner()->GetName()));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("%s is aiming  at: %s from %s"), *(GetOwner()->GetName()), *((HitLocation).ToString()), *(Barrel->GetComponentLocation().ToString()));
	UWorld* World = GetWorld();
	if (World) {
		DrawDebugLine(World, GetOwner()->GetTransform().GetLocation(), HitLocation, FColor::Red, false, -1, 0, 12.333);
	}
}

void UTankAimingComponent::SetBarrel(UStaticMeshComponent* barrel)
{
	this->Barrel = barrel;
}

