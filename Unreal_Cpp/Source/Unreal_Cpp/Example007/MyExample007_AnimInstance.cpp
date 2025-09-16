#include "MyExample007_AnimInstance.h"
#include "MyExample007_Character.h"

UMyExample007_AnimInstance::UMyExample007_AnimInstance() {
}

void UMyExample007_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

	// get character kind of UAnimInstance::TryGetPawnOwner
	auto* Mesh = GetSkelMeshComponent();
	if (!Mesh) return;

	MyCharacter = MyActorUtil::GetActor<AMyExample007_Character>(Mesh->GetOwner());
	if (!MyCharacter)
		return;

	_UpdateMove();
	_UpdateAim();
	_UpdateSlotWeight();
}

void UMyExample007_AnimInstance::_UpdateMove() {
	if (!MyCharacter)
		return;

	auto* MovementComponent = MyCharacter->GetMovementComponent();

	auto vel = MovementComponent->Velocity;
	vel = MyCharacter->GetTransform().InverseTransformVector(vel);
	vel /= MovementComponent->GetMaxSpeed();

	MoveForward = vel.X;
	MoveRight	= vel.Y;

	MyCrouch = MyCharacter->MyCrouch;
}

void UMyExample007_AnimInstance::_UpdateAim() {
	if (!MyCharacter)
	{
		AimUp = 0;
		AimRight = 0;
	}
	else
	{
		MyCharacter->CalcAimOffset(AimUp, AimRight);
	}
}

void UMyExample007_AnimInstance::_UpdateSlotWeight()
{
	static FName UpperName(TEXT("Upper"));
	//_DumpSlotNames();
	UpperSlotWeight = GetMontageSlotWeight(UpperName);
}

void UMyExample007_AnimInstance::NativeInitializeAnimation() {
	UpperSlotWeight = 0;
}

float UMyExample007_AnimInstance::GetMontageSlotWeight(FName slot)
{
	float outWeight = 0;

	// kind of UAnimInstance::GetActiveMontageInstance
	int32 const NumInstances = MontageInstances.Num();
	for (int32 InstanceIndex = NumInstances - 1; InstanceIndex >= 0; InstanceIndex--) {
		const FAnimMontageInstance* MontageInstance = MontageInstances[InstanceIndex];
		if (!MontageInstance || !MontageInstance->IsActive()) continue;
		if (!MontageInstance->Montage->IsValidSlot(slot)) continue;
		outWeight += MontageInstance->GetWeight();
	}

	outWeight = FMath::Clamp(outWeight, 0.0f, 1.0f);
	return outWeight;
}

void UMyExample007_AnimInstance::_DumpSlotNames()
{
	int32 const NumInstances = MontageInstances.Num();
	if (NumInstances <= 0)
		return;

	MY_LOG_WARNING(TEXT("Montage NumInstances = {}"), NumInstances);
	for (int32 InstanceIndex = NumInstances - 1; InstanceIndex >= 0; InstanceIndex--)
	{
		const FAnimMontageInstance* MontageInstance = MontageInstances[InstanceIndex];
		if (!MontageInstance || !MontageInstance->IsActive())
			continue;

		MY_LOG_WARNING(TEXT("Montage GetCurrentSection = {}"), MontageInstance->GetCurrentSection());
		if (!MontageInstance->Montage)
			continue;

		auto& tracks = MontageInstance->Montage->SlotAnimTracks;
		for (auto& track : tracks)
		{
			MY_LOG_WARNING(TEXT("Montage SlotName = {}"), track.SlotName);
		}
	}
}
