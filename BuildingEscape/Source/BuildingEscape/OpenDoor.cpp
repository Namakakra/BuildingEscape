// Copyright Panos Philippou 2016

#include "BuildingEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();

	if (PressurePlate) // Not sure why used, but code doesn't work without.
	{
		{
			ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
		}
	}

}

void UOpenDoor::OpenDoor()
{
	//Set the door rotation
	Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
}

void UOpenDoor::CloseDoor()
{
	//Set the door rotation
	Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the Trigger Volume
	// If the actor that opens is in the volume


	if (PressurePlate)
	{
		if (PressurePlate->IsOverlappingActor(ActorThatOpens))
		{
			OpenDoor();
			LastDoorOpenTime = GetWorld()->GetTimeSeconds();
		}
	
		if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
		{
			CloseDoor();
		}
	}

}
