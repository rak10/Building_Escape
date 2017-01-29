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

	///Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	//ray-cast out to reach distance (perhaps we need provate variable to store that reach
	//LineTraceSingleByObject returns boolean but it needs an FHIT result, so we create it
	//But it is an OUT parameter as it gives us the values so we mark it as an OUT. Its like we give the function an
	//envelope which has arguments, and it gives back the values but in that same envelope
	///To find out what is the kind of argument we need, we can just type it in and intelliSense will give us some info
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
		);

	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line Trace hit; %s "), *(ActorHit->GetName()))
	}
	//see what we hit
}

