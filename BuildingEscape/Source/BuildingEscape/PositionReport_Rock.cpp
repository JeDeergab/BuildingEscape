// Fill out your copyright notice in the Description page of Project Settings.

#include "PositionReport_Rock.h"

// Sets default values for this component's properties
UPositionReport_Rock::UPositionReport_Rock()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPositionReport_Rock::BeginPlay()
{
	Super::BeginPlay();
	AActor * MyObject = GetOwner();

	UE_LOG(LogTemp, Warning, TEXT("This actor is %s reporting from: %s "), *(*MyObject).GetName(), *(*MyObject).GetActorLocation().ToString());
	
}


// Called every frame
void UPositionReport_Rock::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

