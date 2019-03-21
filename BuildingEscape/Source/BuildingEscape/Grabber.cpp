/// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Gameframework/Actor.h"
#include "Engine/World.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/Core/Public/Math/Rotator.h"
#include "Runtime/Engine/Classes/Engine/World.h" 
#include "Runtime/Engine/Classes/Engine/EngineTypes.h"
#include "Runtime/Engine/Public/CollisionQueryParams.h"
#include "Components/PrimitiveComponent.h"
#include "CoreMinimal.h"

///OUT absolutely does NOTHING it's a MACRO for reminding it's unimportant.
#define OUT

/// Sets default values for this component's properties
UGrabber::UGrabber()
{
	/// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	/// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


/// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting in!"));

	PhysicsHandle_Containers();
	InputComponent_Containers();

}

/// Called every frame
/// PhysicsHandle, Grab Component, and SetTargetLocation
/// Picks up component and releases them at any given location

void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	GetReachLineEnd();

	/// If physics handle is attached
	if(PhysicsHandle->GrabbedComponent)
	{
		/// Move the object we're holding
		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
	}
	
}

/// Look for attach physic handle
void UGrabber::PhysicsHandle_Containers()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}

/// Look for attach InputComponent (Only appears on run-time)
void UGrabber::InputComponent_Containers()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent)
	{
		/// Bind the input axis
		InputComponent->BindAction
		(
			"Grab", /// Name of Input
			IE_Pressed, /// When pressed
			this, /// References to Component
			&UGrabber::Grab /// Points to Functions
		);

		InputComponent->BindAction
		(
			"Release", /// Name of Input
			IE_Released, /// When pressed
			this, /// References to Component
			&UGrabber::Release /// Points to Functions
		);
	}
	else
	{
		/// PawnInputComponent0 is found
		UE_LOG(LogTemp, Error, TEXT("Missing Pawn Input Component %s"), *GetOwner()->GetName());
	}
}

///Ray-cast and grab what's in reach
void UGrabber::Grab()
{

	/// Declaring Functions
	FHitResult HitResult;
	FName NO_NAME = ""; /// No name value
	UPrimitiveComponent * ComponentToGrab; /// Creates a variable for ComponentToGrab
	AActor * ActorHit;

	/// LINE TRACE and see if we reach any actors with physics body collisions channel set
	HitResult = GetFirstPhysicsBodyInReach();
	ComponentToGrab = HitResult.GetComponent();
	ActorHit = HitResult.GetActor();

	/// If we hit something then attach a physics handle
	if (ActorHit)
	{
		/// attach physics handle
		PhysicsHandle->GrabComponent
		(
			ComponentToGrab, /// Whatever component it was being hit to be grab
			NO_NAME, /// There's no in-BoneName
			ComponentToGrab->GetOwner()->GetActorLocation(), /// The Location of the component being grab
			true /// Allow to rotate
		);
	}
}

///Ray-cast and release what's in reach
void UGrabber::Release()
{
	PhysicsHandle->ReleaseComponent();
}

/// Gets component that's in front of the viewpoint
const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{

	/// Line-Trace (AKA Ray-cast) out to reach this distance
	FHitResult HitResult;
	FCollisionQueryParams TraceParameter(FName(TEXT("")), false, GetOwner());
	
	GetWorld()->LineTraceSingleByObjectType
	(
		HitResult, /// What it touches
		GetReachLineStart(), /// Where it starts
		GetReachLineEnd(), /// Where it ends
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), /// What the object types is
		TraceParameter /// Where to either player or visible collisions
	);

	/// See what we hit
	AActor * FoundActor = HitResult.GetActor(); /// Get the actor

	if (FoundActor)
	{
		FString ObjectNameFOUND = FoundActor->GetName();
		UE_LOG(LogTemp, Warning, TEXT("This is a %s"), *ObjectNameFOUND); /// Calls out the name of actor
	}

	return HitResult;
}

/// Returns current start of reach line
FVector UGrabber::GetReachLineStart()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotator;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
	(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotator
	);

	return PlayerViewPointLocation;
}

/// Returns current end of reach line
FVector UGrabber::GetReachLineEnd()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotator;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
	(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotator
	);

	return PlayerViewPointLocation + PlayerViewPointRotator.Vector()*reach; // The end of the viewpoint reach
}