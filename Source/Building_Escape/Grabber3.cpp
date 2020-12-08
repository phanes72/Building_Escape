// Copyright Patrick Hanes 2020

#include "Grabber3.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"



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
	
	// Checking for Physics Handle Component
	PhysicsHandle = GetOwner() -> FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{

	} 
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("No Physics Handle componenet found: %s"), *GetOwner()->GetName());
	}

	InputComponent = GetOwner() -> FindComponentByClass<UInputComponent>();
	if(InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Input component found"), *GetOwner()->GetName());
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber3::Grab);
	}
			
}

void UGrabber3::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber Pressed"));
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

	
	// Draw a line from player showing the reach	
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(0, 255, 0),
		false, 
		0.f,
		0,
		5.f 
	);
	
	// Logging out to test
	
	// Get players viewpoint
	//Controller.GetPlayerViewPoint();

	// Ray-cast out to a certain distance (reach) // private member variable
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	// See what it hits
	AActor* ActorHit = Hit.GetActor();

	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line trace has hit %s"), *(ActorHit->GetName()));
	}	

}

