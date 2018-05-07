// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "LublinCharacter.generated.h"

class UInteractableComponent;
UCLASS()
class LUBLIN_API ALublinCharacter : public ACharacter
{
	GENERATED_BODY()
protected:
	// Zmienna przechowujaca aktualnie trace'owany obiekt
	//UPROPERTY(Category ="Line Traceing", BlueprintReadOnly, VisibleAnywhere)
	//AActor * aInteractedObject;
	/* Line tracujaca funkcja
	do dodania
	@param ltObjectsToIngore -> lista objektow do zignorowania, w naszym wypadku jest to lista inicjalizowana w konstruktorze
	*/
	// Zakomentowane bo moze sie pozniej przydac, zadecydowac przy systemie podnoszenia itemow
	//UFUNCTION(BlueprintCallable, Category = "Line Traceing")
		//void LineTrace();

private:

	// Komponent odpowiedzialny za podnoszenie i upuszczanie pzedmiotow
	UPROPERTY(EditAnywhere)
	UInteractableComponent*  InteractablePhysicsComponent = nullptr;

	/*
	Takes nothing
	returns nothing
	called to initiate pickup sequence, is here mostly for pointer protection
	*/
	UFUNCTION(BlueprintCallable, Category = "Picking up")
		void pickUp();

	/*
	Takes nothing
	returns nothig
	called to release item from player hold. implemented for pointer protection as whole process is happening in component
	*/
	UFUNCTION(BlueprintCallable, Category = "Picking up")
		void releaseItem();

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

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		bool JumpButtonDown;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
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