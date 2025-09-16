#include "MyExample006_AnimInstance.h"
#include "MyExample006_Character.h"

UMyExample006_AnimInstance::UMyExample006_AnimInstance() {
}

void UMyExample006_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

	// get character kind of UAnimInstance::TryGetPawnOwner
	auto* Mesh = GetSkelMeshComponent();
	if (!Mesh) return;

	MyCharacter = MyActorUtil::GetActor<AMyExample006_Character>(Mesh->GetOwner());
	if (!MyCharacter)
		return;

	_UpdateMove();
	_UpdateAim();
}

void UMyExample006_AnimInstance::_UpdateMove() {
	auto* MovementComponent = MyCharacter->GetMovementComponent();

	auto vel = MovementComponent->Velocity;
	vel = MyCharacter->GetTransform().InverseTransformVector(vel);
	vel /= MovementComponent->GetMaxSpeed();

	MoveForward = vel.X;
	MoveRight	= vel.Y;

	MyCrouch = MyCharacter->MyCrouch;
}

void UMyExample006_AnimInstance::_UpdateAim() {
	if (auto* t = MyCharacter->Target.Get())
	{
		auto TargetLoc = t->GetActorLocation();
		auto aim = MyCharacter->GetTransform().InverseTransformPosition(TargetLoc);
		auto Rot = aim.Rotation();
		AimUp	 = Rot.Pitch;
		AimRight = Rot.Yaw;
	}
	else
	{
		AimUp = 0;
		AimRight = 0;
	}
}
