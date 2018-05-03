// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableComponent.generated.h"

class UPhysicsHandleComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LUBLIN_API UInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractableComponent();
	/*
	Called to pick up item
	*/
	UFUNCTION(BlueprintCallable, Category = "Pickup") // Exposing function to blueprints as it might come handy
		void pickUp(FVector StartLocation);
	
	/*
	Called to release item from hold
	*/
	UFUNCTION(BlueprintCallable, Category = "Pickup") // Exposing function to blueprints as it might come handy
		void release();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
private:
	/*
	Gets physical handle from player pawn, and sets its pointer reference to podnosnik for future use.
	*/
	void setUpPhysicsComponent();

	// Item thats currently picked by player
	AActor* pickedItem = nullptr;
	// Physics component that is required to grab an object, leaving it to be set from blueprint for designer use :)
	UPROPERTY(EditAnywhere, Category = "Pickup")
	UPhysicsHandleComponent* podnosnik = nullptr;
	// Defines how far should the character reach to pickup object
	UPROPERTY(EditAnywhere, Category = "Pickup")
		float grabDistance = 20.0f; // jakis sensowny  def value TODO znalezc sensowniejszy def value

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};
