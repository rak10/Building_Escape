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
	FindPhysicsHandleComponent();
	SetupInputComponent();
	//UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty"));
	// ...
	
	

}

///Look for attached physics handle
void UGrabber::FindPhysicsHandleComponent()
{

	///Look for attached Physics Handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		//Physics handle is found
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component"), *GetOwner()->GetName())
	}
}

///Look for attached inout component (only appears at run time)
void UGrabber::SetupInputComponent()
{
	//Look for attached Input component (only appears at runt ime)
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing input component"), *GetOwner()->GetName())
	}
}


void UGrabber::Grab()
{
	
	///LINE TRACE try and reach any actors with physics body collision channel set
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();

		///If we hit something then attach a physics handle
	if (ActorHit)
	{
		//TODO attach physics handle
		PhysicsHandle->GrabComponent(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(), 
			true //allow rotation
		);
	}

}

void UGrabber::Release()
{
	PhysicsHandle->ReleaseComponent();
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

			
	// if hte physics handle is attached
	if (PhysicsHandle->GrabbedComponent)
	{

		//move the object we are holding
		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
	}

}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{

	///Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	//ray-cast out to reach distance (perhaps we need provate variable to store that reach
	//LineTraceSingleByObject returns boolean but it needs an FHIT result, so we create it
	//But it is an OUT parameter as it gives us the values so we mark it as an OUT. Its like we give the function an
	//envelope which has arguments, and it gives back the values but in that same envelope
	///To find out what is the kind of argument we need, we can just type it in and intelliSense will give us some info
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		GetReachLineStart(),
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

		return HitResult;
}

FVector UGrabber::GetReachLineStart()
{
	///Get player viewpoint this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	//Void getter GetPlayerViewpoint takes two arguments, and puts the values in them. We know it puts values in them since it is a void getter, 
	//so it gets values but it places them in the arguments passed to it, which means they will constantly change
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	return PlayerViewPointLocation;

}


FVector UGrabber::GetReachLineEnd()
{
	///Get player viewpoint this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	//Void getter GetPlayerViewpoint takes two arguments, and puts the values in them. We know it puts values in them since it is a void getter, 
	//so it gets values but it places them in the arguments passed to it, which means they will constantly change
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	return PlayerViewPointLocation + (PlayerViewPointRotation.Vector()*Reach);

}
