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
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	// Handles input for moving forward and backward.
	UFUNCTION()
		void MoveForward(float AxisValue);

	// Handles input for moving right and left.
	UFUNCTION()
		void MoveRight(float AxisValue);

	//Handles jumping.
	UFUNCTION()
		void StartJump();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool JumpButtonDown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool CrouchButtonDown;

	UFUNCTION()
		void QuitLublin();
	UFUNCTION()
		void StopJump();
	UFUNCTION()
		void OnCrouch();
	UFUNCTION()
		void OnCrouchEnd();
	UPROPERTY(EditAnywhere)
		USpringArmComponent* OurCameraSpringArm;
	UCameraComponent* OurCamera;

	//Input variables
	FVector2D MovementInput;
	FVector2D CameraInput;
	float ZoomFactor;
	bool bZoomingIn;

	void PitchCamera(float AxisValue);
	void YawCamera(float AxisValue);
	void ZoomIn();
	void ZoomOut();

	//Camera
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* FPSCameraComponent;

};