// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"

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
	DoorOpening();

	FRotator GetRotation = (*TheDoor).GetActorRotation();

	float a = GetRotation.Pitch;
	float b = GetRotation.Yaw;
	float c = GetRotation.Roll;	

	FRotator CallRotation
	(
		a, ///_> Pitch
		b, ///_> Yaw
		c ///_> Roll
	);

	UE_LOG(LogTemp, Warning, TEXT("The rotational value of the door is: %s"), *CallRotation.ToString());
}

void UOpenDoor::DoorOpening()
{
	(*TheDoor).SetActorRotation(FRotator(0.f, yaw, 0.f));

	

}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

