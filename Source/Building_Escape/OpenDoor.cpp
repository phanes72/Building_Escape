// Copyright Patrick Hanes 2020


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
	

}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FRotator CurrentRotation = GetOwner() -> GetActorRotation();	
	float CurrentYaw = CurrentRotation.Yaw;
	FRotator OpenDoor {0.f, 90.f, 0.f};
	float TargetYaw = -90.f;
	OpenDoor.Yaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, 1);
	GetOwner()->SetActorRotation(OpenDoor); 


	//Log current roation values
	UE_LOG(LogTemp, Warning, TEXT("%s"), *CurrentRotation.ToString());
	UE_LOG(LogTemp, Warning, TEXT("The YAW is %f"), CurrentRotation.Yaw);
}

