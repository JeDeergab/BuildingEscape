// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/TriggerVolume.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnOpenDoor;

	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnCloseDoor;

private:
	UPROPERTY(EditAnywhere)
		ATriggerVolume * PressurePlate; /// The trigger volume to open door

	UPROPERTY(EditAnywhere)
		float TriggerMass = 30.0f;

		AActor * Owner; /// The Owning door

		// Returns total mass in kilograms
		float GetTotalMassOfActorsOnPlate();

		
};
