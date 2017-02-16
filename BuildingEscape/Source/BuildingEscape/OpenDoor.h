// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	float GetTotalMassOfActorsOnPlate();

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnOpen;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnClose;


private:

	UPROPERTY(EditAnywhere)
	float TriggerMass = 30.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

		
	//AActor* ActorThatOpens;  //pawn inherits from actor so that we can store something in it if we need
	AActor* Owner = nullptr; //Owner of the door, //Find the owning actor

};
