// Fill out your copyright notice in the Description page of Project Settings.

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
	//pawn is an Actor, so we can store a pointer to a pawn which is a pointer to an AActor. And since
	//pawn inherits from AActor it is ok.
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();

	//OpenDoor();

}

void UOpenDoor::OpenDoor()
{
	//Find the owning actor
	AActor* Owner = GetOwner();

	// Create a rotator
	FRotator NewRotation = FRotator(0.0f, 50.0f, 0.0f);

	// Set door rotation
	Owner->SetActorRotation(NewRotation);
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	//Poll the trigger volume every frame
	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{ 

	//If the ActorThatOpens is in volume
	OpenDoor();
	}
}

