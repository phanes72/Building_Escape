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

}


// Called when the game starts
void UGrabber3::BeginPlay()
{
	Super::BeginPlay();
	
	FindPhysicsHandle();
	SetupInputComponent();

			
}

void UGrabber3::SetupInputComponent()
{
	InputComponent = GetOwner() -> FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{		
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber3::Grab); // This is the address of the Grab function which is contained in UGrabber3
																				// it doesn't actually call the function but rather tells the method where to go to call
																				// call it when we press our R Mouse Button

		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber3::Release);
	}	
}

// Checking for Physics Handle Component
void UGrabber3::FindPhysicsHandle()
{
	
	PhysicsHandle = GetOwner() -> FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{

	} 
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("No Physics Handle componenet found: %s"), *GetOwner()->GetName());
	}
}

void UGrabber3::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber Pressed"));	

	//If we hit something then attach the physics handle

	//TODO attach physics handle 

	GetFirstPhysicsBodyInReach();
}

void UGrabber3::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber Released"));
	//TODO remove/release the physics handle
}

// Called every frame
void UGrabber3::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// If physics handle is attached
		//Move the object we are holding

	

}

FHitResult UGrabber3::GetFirstPhysicsBodyInReach() const
{
	//Get player's viewpoint
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld() -> GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation, 
		OUT PlayerViewPointRotation
	);

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
	
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

	return Hit;
}
	