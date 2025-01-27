// Fill out your copyright notice in the Description page of Project Settings.

#include "Lublin.h"
#include "CharacterComponents/InteractableComponent.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "LublinCharacter.h"


void ALublinCharacter::pickUp()
{
	// Chronmy wskazniki

	USkeletalMeshComponent* PlayerMesh = this->FindComponentByClass<USkeletalMeshComponent>();
	if (!PlayerMesh) return;
	FVector TracePosition = PlayerMesh->GetSocketLocation("headSocket");
	if (!InteractablePhysicsComponent) return;
	this->InteractablePhysicsComponent->pickUp(TracePosition);

}

void ALublinCharacter::releaseItem()
{
	// Tu tez je chronmy
	if (!InteractablePhysicsComponent) return;
	this->InteractablePhysicsComponent->release();
}

// Sets default values
ALublinCharacter::ALublinCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Camera	
	OurCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	OurCameraSpringArm->SetupAttachment(GetCapsuleComponent());
	OurCameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-60.0f, 0.0f, 0.0f));
	OurCameraSpringArm->TargetArmLength = 400.f;
	OurCameraSpringArm->bEnableCameraLag = true;
	OurCameraSpringArm->CameraLagSpeed = 3.0f;
	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	OurCamera->SetupAttachment(OurCameraSpringArm, USpringArmComponent::SocketName);

	InteractablePhysicsComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("Grab Component"));



	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ALublinCharacter::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("using LublinCharacter"));
	this->InteractablePhysicsComponent = this->FindComponentByClass<UInteractableComponent>();
	if (!InteractablePhysicsComponent) {
		// Makes debugging easier
		UE_LOG(LogTemp, Warning, TEXT("Komponent odpowiedzialny za fizyke nie zostal znaleziony"));
	}

}

// Called every frame
void ALublinCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	



	// this->LineTrace(); might be needed later tho
	{
		if (bZoomingIn)
		{
			ZoomFactor += DeltaTime / 0.5f;         //Zoom in over half a second
		}
		else
		{
			ZoomFactor -= DeltaTime / 0.25f;        //Zoom out over a quarter of a second
		}
		ZoomFactor = FMath::Clamp<float>(ZoomFactor, 0.0f, 1.0f);
		//Blend our camera's FOV and our SpringArm's length based on ZoomFactor
		OurCamera->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, ZoomFactor);
		OurCameraSpringArm->TargetArmLength = FMath::Lerp<float>(400.0f, 300.0f, ZoomFactor);
	}

	//Rotate our camera's pitch, but limit it so we're always looking downward
	{
		FRotator NewRotation = OurCameraSpringArm->GetComponentRotation();
		/* Oryginalnie Clamp z zakresu -20.f do 180.0f zmieniony by ulatwic interakcje z obiektami
		*/
		NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + CameraInput.Y,- 70.0f, 40.0f);
		OurCameraSpringArm->SetWorldRotation(NewRotation);
	}
}

// Called to bind functionality to input
void ALublinCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	// Set up "movement" bindings.
	InputComponent->BindAxis("MoveForward", this, &ALublinCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ALublinCharacter::MoveRight);
	InputComponent->BindAxis("CameraPitch", this, &ALublinCharacter::PitchCamera);
	InputComponent->BindAxis("CameraYaw", this, &ALublinCharacter::AddControllerYawInput);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ALublinCharacter::StartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &ALublinCharacter::StopJump);
	InputComponent->BindAction("Quit", IE_Pressed, this, &ALublinCharacter::QuitLublin);
	InputComponent->BindAction("Crouch", IE_Pressed, this, &ALublinCharacter::OnCrouch);
	InputComponent->BindAction("Crouch", IE_Released, this, &ALublinCharacter::OnCrouchEnd);
	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &ALublinCharacter::ZoomIn);
	InputComponent->BindAction("ZoomIn", IE_Released, this, &ALublinCharacter::ZoomOut);
	InputComponent->BindAction("Grab", IE_Pressed, this, &ALublinCharacter::pickUp);
	InputComponent->BindAction("Grab", IE_Released, this, &ALublinCharacter::releaseItem);
}

void ALublinCharacter::MoveForward(float AxisValue)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, AxisValue);
}

void ALublinCharacter::MoveRight(float AxisValue)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, AxisValue);
}

void ALublinCharacter::StartJump()
{
	if (CanJumpInternal()) {
		JumpButtonDown = true;
	}
	UCharacterMovementComponent &mov = *Cast <UCharacterMovementComponent>(GetMovementComponent());
	if (mov.Velocity.X || mov.Velocity.Y)
		Jump();
}

void ALublinCharacter::OnCrouch()
{
	CrouchButtonDown = true;
}

void ALublinCharacter::OnCrouchEnd()
{
	CrouchButtonDown = false;
}

void ALublinCharacter::PitchCamera(float AxisValue)
{
	CameraInput.Y = AxisValue;
}

void ALublinCharacter::YawCamera(float AxisValue)
{
	CameraInput.X = AxisValue;
}

void ALublinCharacter::ZoomIn()
{
	bZoomingIn = true;
}

void ALublinCharacter::ZoomOut()
{
	bZoomingIn = false;
}


void ALublinCharacter::QuitLublin()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), TEnumAsByte<EQuitPreference::Type>::EnumType::Quit);
}

void ALublinCharacter::StopJump()
{
	JumpButtonDown = false;

}
// TODO zadecydowac co z line traceiniem. Moze sie przydac do callowania co klatke w przypadku robienia User Interface (np najazd celownikiem wyswietla nazwe przedmiotu)
/*
void ALublinCharacter::LineTrace()
{
	// Zawiera dane o hitach z traceingu
	FHitResult hit;
	// Punkt poczatkowy ray traceingu
	FVector startVector = this->OurCamera->GetComponentLocation();
	// Koniec tracingu
	FVector endVector = startVector + (this->OurCamera->GetForwardVector() * 300.0f);
	GetWorld()->LineTraceSingleByChannel(hit, startVector, endVector, ECC_Camera);
	// Struct przechowujacy obiekty ktorych traceowaniem jestem zainteresowany

	if (hit.bBlockingHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("HIT"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NOT HIT"));
	}
}
*/