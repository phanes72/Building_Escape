// Copyright Patrick Hanes 2020
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "OpenDoor.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	InitialYaw = GetOwner() -> GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	TargetYaw += InitialYaw;

	if(!PressurePlate)
	{
		FString Actor = GetOwner() -> GetName();
		UE_LOG(LogTemp, Error, TEXT("%s is not configured for the pressure plate!"), *Actor);
	}

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (PressurePlate && PressurePlate-> IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor(DeltaTime);
		// When the door was last opened = DoorLastOpened
		DoorLastOpened = GetWorld() -> GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f"), DoorLastOpened);
	} else 
	{
		//if door has been open longer than x seconds then shut the door = DoorCloseDelay
		if(GetWorld() -> GetTimeSeconds() - DoorLastOpened > DoorCloseDelay)
		{
			CloseDoor(DeltaTime);
		}
		
	}
 }

 void UOpenDoor::OpenDoor(float DeltaTime)
 {
	CurrentYaw = FMath::Lerp(CurrentYaw, TargetYaw, DeltaTime * 0.8f);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
 }

 void UOpenDoor::CloseDoor(float DeltaTime)
 {
	CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, DeltaTime * 2.0f);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
 }

