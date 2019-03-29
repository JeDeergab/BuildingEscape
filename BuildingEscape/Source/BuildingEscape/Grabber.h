// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	/// Sets default values for this component's properties
	UGrabber();

protected:
	/// Called when the game starts
	virtual void BeginPlay() override;

public:	
	/// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	/// What we use to attach component and move them
	UPhysicsHandleComponent * PhysicsHandle = nullptr;

	/// Bind keys for Grab and Release
	UInputComponent * InputComponent = nullptr;

	/// gives reach 
	float reach = 100.0f;

	///Ray-cast and grab what's in reach
	void Grab();

	///Ray-cast and release what's in reach
	void Release();

	/// Look for attach physic handle
	void PhysicsHandle_Containers();

	/// Look for attach InputComponent (Only appears on run-time)
	void InputComponent_Containers();

	/// Gets component that's in front of the viewpoint
	const FHitResult GetFirstPhysicsBodyInReach();

	/// Returns current start of reach line
	FVector GetReachLineStart();

	/// Returns current end of reach line
	FVector GetReachLineEnd();

};
