#include "MyExample004_BlendTriggerVolume.h"
#include "Components/BoxComponent.h"
#include "../Unreal_CameraCharacter.h"
#include "Camera/CameraActor.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

AMyExample004_BlendTriggerVolume::AMyExample004_BlendTriggerVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	MyCDO::CreateComponent(this, OverlapVolume);
	MyCDO::CreateComponent(this, moveDirection);
}

void AMyExample004_BlendTriggerVolume::BeginPlay()
{
	Super::BeginPlay();
}

void AMyExample004_BlendTriggerVolume::NotifyActorBeginOverlap(AActor* HitResultActor)
{
	if (auto* Unreal_CameraCharacter = Cast<AUnreal_CameraCharacter>(HitResultActor))
	{
		if (auto* PC = Cast<APlayerController>(Unreal_CameraCharacter->GetController()))
		{
			if (auto* p = CameraToFind.Get())
			{
				PC->SetViewTargetWithBlend(p, CameraBlendTime, EViewTargetBlendFunction::VTBlend_Linear);
				
				FVector ForwardVector;
				FVector RightVector;
				GetMovementVectors(ForwardVector, RightVector);
				Unreal_CameraCharacter->LockMovementDirection(ForwardVector, RightVector);
			}
		}
	}
}

void AMyExample004_BlendTriggerVolume::NotifyActorEndOverlap(AActor* HitResultActor)
{
	if (auto* Unreal_CameraCharacter = Cast<AUnreal_CameraCharacter>(HitResultActor))
	{
		if (auto* PC = Cast<APlayerController>(Unreal_CameraCharacter->GetController()))
		{
			PC->SetViewTargetWithBlend(PC->GetPawn(), CameraBlendTime, EViewTargetBlendFunction::VTBlend_Linear);
			Unreal_CameraCharacter->UnlockMovementDirection();
		}
	}
}

void AMyExample004_BlendTriggerVolume::GetMovementVectors(FVector& ForwardVector, FVector& RightVector)
{
	if (moveDirection)
	{
		ForwardVector = moveDirection->GetForwardVector();
		RightVector = moveDirection->GetRightVector();
		//UpVector = moveDirection->GetUpVector();
	}
	else
	{
		MY_LOG_ERROR(TEXT("{} missing moveDirection"), *GetNameSafe(this));
	}
}