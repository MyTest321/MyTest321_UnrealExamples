// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyExample001_Character.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"

//////////////////////////////////////////////////////////////////////////
// AMyExample001_Character

AMyExample001_Character::AMyExample001_Character()
{
	MY_CDO_FINDER(DefaultMappingContext,	TEXT("/Script/EnhancedInput.InputMappingContext'/Game/ThirdPerson/Input/IMC_Default'"));
	MY_CDO_FINDER(IA_Jump,					TEXT("/Script/EnhancedInput.InputAction'/Game/ThirdPerson/Input/Actions/IA_Jump'"));
	MY_CDO_FINDER(IA_Move,					TEXT("/Script/EnhancedInput.InputAction'/Game/ThirdPerson/Input/Actions/IA_Move.IA_Move'"));
	MY_CDO_FINDER(IA_CameraPos,				TEXT("/Script/EnhancedInput.InputAction'/Game/ThirdPerson/Input/Actions/IA_CameraPos.IA_CameraPos'"));

	GetCapsuleComponent()->InitCapsuleSize(35.f, 90.0f);
		
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw   = false;
	bUseControllerRotationRoll  = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity				= 700.f;
	GetCharacterMovement()->AirControl					= 0.35f;
	GetCharacterMovement()->MaxWalkSpeed				= 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed			= 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking	= 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling	= 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AMyExample001_Character::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AMyExample001_Character::BeginPlay()
{
	Super::BeginPlay();
	SetCameraPos(MyEnum::ToEnum<ECameraPos>(0));
}

void AMyExample001_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!EnhancedInputComponent)
	{
		MY_LOG_ERROR(TEXT("{} missing UEnhancedInputComponent"), *GetNameSafe(this));
		return;
	}

	auto BindAction = [&](const TCHAR* ActionName, UInputAction* Action, ETriggerEvent Event, void (ThisClass::*Func)(const FInputActionValue& Value)) {
		if (!Action)
			MY_LOG_ERROR(TEXT("InputAction {} is null"), ActionName);
		else
			EnhancedInputComponent->BindAction(Action, Event, this, Func);
	};

	#define MY_BIND_INPUT_ACTION(Action, Event) \
		BindAction(TEXT(#Action), Action, ETriggerEvent::Event, &ThisClass::Action##_##Event); \
	//---
		MY_BIND_INPUT_ACTION(IA_Move,		Triggered);
		MY_BIND_INPUT_ACTION(IA_Jump,		Started);
		MY_BIND_INPUT_ACTION(IA_Jump,		Completed);
		MY_BIND_INPUT_ACTION(IA_CameraPos,	Started);
	#undef MY_BIND_INPUT_ACTION
}

void AMyExample001_Character::IA_Move_Triggered(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		float		   Yaw		= Rotation.Yaw + CameraOffset;
		const FRotator YawRotation(0, Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AMyExample001_Character::IA_Jump_Started(const FInputActionValue& Value) {
	Jump();
}

void AMyExample001_Character::IA_Jump_Completed(const FInputActionValue& Value) {
	StopJumping();
}

void AMyExample001_Character::IA_CameraPos_Started(const FInputActionValue& Value)
{
	auto NewCameraPos = static_cast<ECameraPos>((MyEnum::ToInt(CameraPos) + 1) % MyEnum::ToInt(EMyExample001_CameraPos::_End));
	SetCameraPos(NewCameraPos);
}

void AMyExample001_Character::SetCameraPos(ECameraPos NewCameraPos)
{
	if (CameraPos == NewCameraPos)
		return;
	MY_LOG_ON_SCREEN(TEXT("Cur ECameraPos: {}"), NewCameraPos);

	CameraPos = NewCameraPos;

	FVector	 NewTargetOffset;
	FRotator NewRotator = FRotator::ZeroRotator;
	float	 NewCameraOffset = 0;
	switch (CameraPos)
	{
		case ECameraPos::SW:
		{
			NewTargetOffset.Set(0, -400, 300);
			NewRotator.Pitch	= -25;
			NewRotator.Yaw		= 45;
			NewRotator.Roll		= 0;
			NewCameraOffset		= 45.f;
		} break;
		case ECameraPos::SE:
		{
		
			NewTargetOffset.Set(0, 400, 300);
			NewRotator.Pitch	= -25;
			NewRotator.Yaw		= -45;
			NewRotator.Roll		= 0;
			NewCameraOffset		= -45.f;
		} break;
		case ECameraPos::NE:
		{
			NewTargetOffset.Set(800, 400, 300);
			NewRotator.Pitch = -25;
			NewRotator.Yaw = -135;
			NewRotator.Roll = 0;
			NewCameraOffset = -135.f;
		} break;
		case ECameraPos::NW:
		{
			NewTargetOffset.Set(800, -400, 300);
			NewRotator.Pitch = -25;
			NewRotator.Yaw = 135;
			NewRotator.Roll = 0;
			NewCameraOffset = 135.f;
		} break;
		default: {
			MY_ASSERT(false);
			return;
		}
	}

	CameraBoom->TargetOffset = NewTargetOffset;
	FollowCamera->SetRelativeRotation(NewRotator);
	CameraOffset = NewCameraOffset;
}