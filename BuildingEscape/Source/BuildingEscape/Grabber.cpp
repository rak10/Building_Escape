// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "Grabber.h"

#define OUT //preprocessor directive that does NOTHING as there is nothing after OUT, we just use it to mark Viewpoint Location and ROtation
//When it compiles it will replace OUT  in our void getter with nothing
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty"));
	// ...
	
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Get player viewpoint this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	//Void getter GetPlayerViewpoint takes two arguments, and puts the values in them. We know it puts values in them since it is a void getter, 
	//so it gets values but it places them in the arguments passed to it, which means they will constantly change
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
	
	//Log out to test
	//FString ViewPoint = GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint().ToString();
	//FString GrabberObjectPos = GetOwner()->GetTransform().ToString();
	/*UE_LOG(LogTemp, Warning, TEXT("The location is: %s, Position is: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString())*/


	//draw a red trace in world to visualise
	FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector()*Reach);
	//FVector LineTraceEnd = PlayerViewPointLocation + FVector(0.f, 0.f, 50.0f);
	DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor(255, 0, 0), false, 0.f, 0.f, 10.0f);

	//ray-cast out to reach distance (perhaps we need provate variable to store that reach


	//see what we hit
}

