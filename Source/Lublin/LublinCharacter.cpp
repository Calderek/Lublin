// Fill out your copyright notice in the Description page of Project Settings.

#include "Lublin.h"
#include "LublinCharacter.h"


// Sets default values
ALublinCharacter::ALublinCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Camera
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FPSCameraComponent->AttachTo(GetCapsuleComponent());
	FPSCameraComponent->SetRelativeLocation(FVector(25.0f, 1.0f, 74.0f));
	FPSCameraComponent->bUsePawnControlRotation = true;

	//this->GetCharacterMovement()->JumpZVelocity = 600.0f;
	//this->GetCharacterMovement()->AirControl = 0.5f;
}

// Called when the game starts or when spawned
void ALublinCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALublinCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALublinCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	// Set up "movement" bindings.
	InputComponent->BindAxis("MoveForward", this, &ALublinCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ALublinCharacter::MoveRight);
	InputComponent->BindAxis("Turn", this, &ALublinCharacter::AddControllerYawInput);
	InputComponent->BindAxis("LookUpDown", this, &ALublinCharacter::AddControllerPitchInput);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ALublinCharacter::StartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &ALublinCharacter::StopJump);
	InputComponent->BindAction("Quit", IE_Pressed, this, &ALublinCharacter::QuitLublin);
}

void ALublinCharacter::MoveForward(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void ALublinCharacter::MoveRight(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void ALublinCharacter::StartJump()
{

	Jump();

}

void ALublinCharacter::QuitLublin()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), TEnumAsByte<EQuitPreference::Type>::EnumType::Quit);
}

void ALublinCharacter::StopJump()
{
	bPressedJump = false;

}