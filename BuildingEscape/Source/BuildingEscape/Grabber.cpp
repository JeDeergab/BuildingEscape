// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Gameframework/Actor.h"
#include "Engine/World.h"

//OUT absolutely does NOTHING it's a MACRO for reminding it's unimportant.
#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting in!"));
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get player view point this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotator;

				// Gets controller of the player
					GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
						OUT PlayerViewPointLocation,
						OUT PlayerViewPointRotator
					);

	// Gets Player Viewpoint LOCATION and ROTATOR
		FString  Viewpoint_Location_STRING = PlayerViewPointLocation.ToString();
		FString  Viewpoint_Rotator_STRING = PlayerViewPointRotator.ToString();
	
	// LOGS Player Viepoint LOCATION and ROTATOR to TEST
		UE_LOG(LogTemp, Warning, TEXT("%s Player Viewpoint Location and %s Player Viewpoint Rotation"), 
			*Viewpoint_Location_STRING, 
			*Viewpoint_Rotator_STRING
		);

		// NOTE: Example you DON'T HAVE TO create variable to store the Location and Rotator just add .ToString
		// NOTE: UE_LOG(LogTemp, Warning, TEXT("Player Viewpoint Location: %s and Player Viewpoint Rotation: %s"), *PlayerViewPointLocation.ToString, *PlayerViewPointRotator.ToString);
	
	// Ray-cast out to reach this distance

	// See what we hit
}

