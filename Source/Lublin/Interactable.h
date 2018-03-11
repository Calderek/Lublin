// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.generated.h"

UCLASS()
class LUBLIN_API AInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractable();
	// Konstruktor dodatkowo ustawiajacy mesh obiektu
	AInteractable(UStaticMesh NowyMesh);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Mesh ktorego bedzie uzywal nasz przedmiot, typu UStaticMesh
	UPROPERTY(BlueprintReadOnly,Category ="Interactable")
	UStaticMesh* ItemMesh;
	UPROPERTY(BlueprintReadOnly, Category = "Interactable")
	USphereComponent* ItemInteractionSphere;

	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Getter dla item mesha
	UFUNCTION(BlueprintCallable, Category = "Interactable")
		UStaticMesh* GetItemMesh();
	// Setter dla item mesha gdzie @ *newMesh to wskaznik do nowego mesha
	UFUNCTION(BlueprintCallable, Category = "Inreactable")
		void SetItemMesh(UStaticMesh *newMesh);
	// Zwraca sfere kolizji dla mesha
	UFUNCTION(BlueprintCallable, Category = "Inreactable")
		USphereComponent* ReturnInteractionSphere();
	// Funkcja ktora pozwala nam na interakcje
	UFUNCTION(BlueprintCallable, Category = "Interactable")
	virtual void Interact();
	
	
};
