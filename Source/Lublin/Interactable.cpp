// Fill out your copyright notice in the Description page of Project Settings.

#include "Lublin.h"
#include "Interactable.h"


// Sets default values
AInteractable::AInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AInteractable::SetItemMesh(UStaticMesh *newMesh)
{
	this->ItemMesh = newMesh;
}
UStaticMesh* AInteractable::GetItemMesh()
{
	return this->ItemMesh; 
}
USphereComponent* AInteractable::ReturnInteractionSphere()
{ 
	return this->ItemInteractionSphere;
}
void AInteractable::Interact()
{
	FString PickupDebugString = GetName();
	UE_LOG(LogClass, Log, TEXT("You have collected %s"), *PickupDebugString);
}