// Fill out your copyright notice in the Description page of Project Settings.

#include "Lublin.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsHandleComponent.h"
#include "Runtime/Engine/Classes/Components/ActorComponent.h"
#include "InteractableComponent.h"


// Sets default values for this component's properties
UInteractableComponent::UInteractableComponent()
{
	// Ticking is mandatory as its kinda required to move items
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractableComponent::BeginPlay()
{
	Super::BeginPlay();
	setUpPhysicsComponent();
	// ...
	
}
void UInteractableComponent::pickUp(FVector StartLocation)
{
	 // TODO REFACTOR IT!
	// Setup collision parameters
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	// Setup Hit
	FHitResult pickUpHit;
	FRotator TracingRotation;
	FVector TraceStartLocation;
	this->GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(TraceStartLocation, TracingRotation);
	UE_LOG(LogTemp, Warning, TEXT("TracingRotation %s"), *(TracingRotation.Vector().ToString()));
	UE_LOG(LogTemp, Warning, TEXT("TracingStart %s"), *(StartLocation.ToString()));

	FVector EndLocation = StartLocation + TracingRotation.Vector() *  traceDistance;
	UE_LOG(LogTemp, Warning, TEXT("EndLocation %s"), *(EndLocation.ToString()));
	// Start location relative to player camera
	FColor Czerwony;
	Czerwony.R = 255;
	Czerwony.B = 0;
	Czerwony.G = 0;
	//Draw a debug Line
	DrawDebugLine(this->GetWorld(), StartLocation,EndLocation,Czerwony,true,0.0f,1,10);
	GetWorld()->LineTraceSingleByObjectType(
		pickUpHit,
		StartLocation,
		EndLocation,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	AActor* ActorHit = pickUpHit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is hit"), *(ActorHit->GetName()))
	}
	
	auto DoPodniesienia = pickUpHit.GetComponent();
	
	if (!podnosnik) return;
	podnosnik->GrabComponent(
		DoPodniesienia,
		NAME_None,
		DoPodniesienia->GetOwner()->GetActorLocation()
		, true
	);



	// else do nothing
}
void UInteractableComponent::setUpPhysicsComponent()
{
	podnosnik = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (podnosnik) UE_LOG(LogTemp, Warning, TEXT("Znaleziono podnosnik"));
}
void  UInteractableComponent::release()
{
	if (!podnosnik) return;
	// check if theres an item picked 
	if (!pickedItem) return; // return from function protecting pointer
	// else
	// release the picked item
}

// Called every frame
void UInteractableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// zabezpieczamy podnosnik
	if (!podnosnik) return;
	// sprawdzam czy cos jest podniesione
	if (podnosnik->GrabbedComponent)
	{
		// wyliczyc miejsce do przeniesienia
		// przeniesc tam
		podnosnik->SetTargetLocation(GetLineEnd());
	}
	// ...
}
FVector UInteractableComponent::GetLineEnd()
{
	FVector TraceStartLocation;
	FRotator TracingRotation;
	FVector StartPosition = this->GetOwner()->GetActorLocation();
	this->GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(TraceStartLocation, TracingRotation);

	return StartPosition + TracingRotation.Vector() * grabDistance;
}
