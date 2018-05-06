// Fill out your copyright notice in the Description page of Project Settings.

#include "Lublin.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsHandleComponent.h"
#include "Runtime/Engine/Classes/Components/ActorComponent.h"
#include "InteractableComponent.h"


//TODO Zmienic GrabDistance badz liczenie vektora z grab distance tak zeby oduczyc postac telekinezy

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
	// Setup Hit output parameter
	FHitResult pickUpHit;
	if (bLineTracePhysicsBody(StartLocation, pickUpHit))
	{
		auto DoPodniesienia = pickUpHit.GetComponent();

		if (!podnosnik) return;
		podnosnik->GrabComponent(
			DoPodniesienia,
			NAME_None,
			DoPodniesienia->GetOwner()->GetActorLocation()
			, true
		);
	}


	




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
	podnosnik->ReleaseComponent();
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

	FVector TracingRotation = GetTheRotationVector();

	FVector StartPosition = this->GetOwner()->GetActorLocation();
	FVector EndLocation = StartPosition + TracingRotation * grabDistance;

	//Draw a debug Line
	DrawDebugLine(this->GetWorld(), StartPosition, EndLocation, FColor::Orange, true, 0.0f, 1, 10);

	return StartPosition + TracingRotation * grabDistance;
}
FVector UInteractableComponent::GetTheRotationVector()
{
	FRotator TracingRotation;
	FVector TraceStartLocation;
	this->GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(TraceStartLocation, TracingRotation);
	return TracingRotation.Vector();
}

bool UInteractableComponent::bLineTracePhysicsBody(FVector StartLocation, FHitResult & HitResult)
{
	// Setup Collision Query Params
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	FVector TraceRotation = GetTheRotationVector();


	FVector EndLocation = StartLocation + TraceRotation * traceDistance;
	UE_LOG(LogTemp, Warning, TEXT("EndLocation %s"), *(EndLocation.ToString()));
	UE_LOG(LogTemp, Warning, TEXT("TracingRotation %s"), *(TraceRotation.ToString()));
	UE_LOG(LogTemp, Warning, TEXT("TracingStart %s"), *(StartLocation.ToString()));
	// Start location relative to player camera

	return GetWorld()->LineTraceSingleByObjectType(
		HitResult,
		StartLocation,
		EndLocation,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

}
