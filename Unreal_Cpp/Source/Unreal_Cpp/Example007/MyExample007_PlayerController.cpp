#include "MyExample007_PlayerController.h"
#include "MyExample007_Character.h"
#include "GameFramework/Pawn.h"

AMyExample007_PlayerController::AMyExample007_PlayerController()
{
	InputDirection = FVector::Zero();
}

void AMyExample007_PlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	MY_LOG_ON_SCREEN(TEXT("InputDirection {}"), InputDirection);

	BaseTurnRightRate = 45.f;
	BaseLookUpRate = 45.f;

	if (!MyCharacter)
		return;

	auto v = MyCharacter->GetTransform().TransformVector(InputDirection);
	v *= FMath::Clamp(1 - MyCharacter->BlockMoveCurveValue, 0.0f, 1.0f);
	MyCharacter->GetMovementComponent()->AddInputVector(v);
}

void AMyExample007_PlayerController::OnPossess(APawn* aPawn) {
	Super::OnPossess(aPawn);
	MyCharacter = Cast<AMyExample007_Character>(aPawn);

	using T = std::remove_pointer_t<decltype(MyCharacter)>;
	MyCharacter = CastChecked<T>(aPawn);
}

void AMyExample007_PlayerController::OnUnPossess() {
	Super::OnUnPossess();
	MyCharacter = nullptr;
}

void AMyExample007_PlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	SetShowMouseCursor(true);

	// Axis
	InputComponent->BindAxis("Move Forward / Backward", this, &ThisClass::OnInputAxis_MoveForward);
	InputComponent->BindAxis("Move Right / Left",		this, &ThisClass::OnInputAxis_MoveRight);

	InputComponent->BindAxis("TurnRight",		this, &ThisClass::OnInputAxis_TurnRight); // only work when SetShowMouseCursor(false)
	InputComponent->BindAxis("TurnRightRate",	this, &ThisClass::OnInputAxis_TurnRightRate);
	InputComponent->BindAxis("LookUp",			this, &ThisClass::OnInputAxis_LookUp);    // only work when SetShowMouseCursor(false)
	InputComponent->BindAxis("LookUpRate",		this, &ThisClass::OnInputAxis_LookUpRate);

	auto MyBindAction = [&](const FName ActionName
						  , const EInputEvent KeyEvent
						  , FInputActionHandlerSignature::TMethodPtr<ThisClass> Func)
	{
		this->InputComponent->BindAction(ActionName, KeyEvent, this, Func);
	};

	#define MY_BIND_ACTION(ACTION_NAME, MY_EVENT) \
		MyBindAction(#ACTION_NAME, MY_EVENT, &ThisClass::ACTION_NAME##_##MY_EVENT); \
	// ----
		MY_BIND_ACTION(Crouch,	IE_Pressed)
		MY_BIND_ACTION(Equip,	IE_Pressed)
		MY_BIND_ACTION(Fire,	IE_Pressed)
		MY_BIND_ACTION(Jump,	IE_Pressed)
	#undef MY_BIND_ACTION
}

void AMyExample007_PlayerController::OnInputAxis_MoveForward(float Value) { InputDirection.X = Value; }
void AMyExample007_PlayerController::OnInputAxis_MoveRight  (float Value) { InputDirection.Y = Value; }

void AMyExample007_PlayerController::OnInputAxis_TurnRight(float Value)
{
//	MY_LOG_ON_SCREEN(TEXT("OnInputAxis_TurnRight {}"), Value);
	AddYawInput(Value);
}
void AMyExample007_PlayerController::OnInputAxis_TurnRightRate(float Value)
{
//	MY_LOG_ON_SCREEN(TEXT("OnInputAxis_TurnRightRate {}"), Value * BaseTurnRightRate * GetWorld()->GetDeltaSeconds());
	AddYawInput(Value * BaseTurnRightRate * GetWorld()->GetDeltaSeconds());
}

void AMyExample007_PlayerController::OnInputAxis_LookUp(float Value)
{
	AddPitchInput(Value);
}
void AMyExample007_PlayerController::OnInputAxis_LookUpRate(float Value)
{
	AddPitchInput(Value * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMyExample007_PlayerController::Crouch_IE_Pressed()
{
	MY_LOG_INFO(TEXT("Crouch_IE_Pressed"));
	if (!MyCharacter)
		return;
	MyCharacter->MyCrouch = !MyCharacter->MyCrouch;
}
void AMyExample007_PlayerController::Equip_IE_Pressed()
{
	MY_LOG_INFO(TEXT("Equip_IE_Pressed"));
	if (!MyCharacter)
		return;
	MyCharacter->MyEquip();
}
void AMyExample007_PlayerController::Fire_IE_Pressed()
{
	MY_LOG_INFO(TEXT("Fire_IE_Pressed"));
	if (!MyCharacter)
		return;
	MyCharacter->MyFire();
}

void AMyExample007_PlayerController::Jump_IE_Pressed()
{
	MY_LOG_INFO(TEXT("Jump_IE_Pressed"));
	if (!MyCharacter)
		return;
	MyCharacter->Jump();
}