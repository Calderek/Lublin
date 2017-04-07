// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "LublinCharacter.generated.h"

UCLASS()
class LUBLIN_API ALublinCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALublinCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	// Handles input for moving forward and backward.
	UFUNCTION()
		void MoveForward(float Value);

	// Handles input for moving right and left.
	UFUNCTION()
		void MoveRight(float Value);

	//Handles jumping.
	UFUNCTION()
		void StartJump();

	UFUNCTION()
		void QuitLublin();
	UFUNCTION()
		void StopJump();

	//Camera
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* FPSCameraComponent;
	
};
