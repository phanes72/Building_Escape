// Copyright Patrick Hanes 2020

#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Grabber3.h"

#define OUT

// Sets default values for this component's properties
UGrabber3::UGrabber3()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber3::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));
	
}


// Called every frame
void UGrabber3::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Get player's location
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld() -> GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation, 
		OUT PlayerViewPointRotation
		);

	UE_LOG(LogTemp, Warning, TEXT("%s"), *PlayerViewPointLocation.ToString());
	UE_LOG(LogTemp, Warning, TEXT("%s"), *PlayerViewPointRotation.ToString());

	// Logging out to test
	
	// Get players viewpoint
	//Controller.GetPlayerViewPoint();

	// Ray-cast out to a certain distance (reach) // private member variable

	// See what it hits
}

