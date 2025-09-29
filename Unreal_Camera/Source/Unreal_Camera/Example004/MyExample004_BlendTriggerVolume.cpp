#include "MyExample004_BlendTriggerVolume.h"
#include "Components/BoxComponent.h"
#include "../Unreal_CameraCharacter.h"
#include "Camera/CameraActor.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

AMyExample004_BlendTriggerVolume::AMyExample004_BlendTriggerVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	MyCDO::CreateComponent(this, OverlapVolume);
}

void AMyExample004_BlendTriggerVolume::BeginPlay()
{
	Super::BeginPlay();
}

void AMyExample004_BlendTriggerVolume::NotifyActorBeginOverlap(AActor* HitResultActor)
{
	if (auto* PlayerCharacterCheck = Cast<AUnreal_CameraCharacter>(HitResultActor))
	{
		if (auto* PlayerCharacterController = Cast<APlayerController>(PlayerCharacterCheck->GetController()))
		{
			if (auto* p = CameraToFind.Get())
			{
				PlayerCharacterController->SetViewTargetWithBlend(p, CameraBlendTime, EViewTargetBlendFunction::VTBlend_Linear);
			}
		}
	}
}

void AMyExample004_BlendTriggerVolume::NotifyActorEndOverlap(AActor* HitResultActor)
{
	if (auto* PlayerCharacterCheck = Cast<AUnreal_CameraCharacter>(HitResultActor))
	{
		if (auto* PlayerCharacterController = Cast<APlayerController>(PlayerCharacterCheck->GetController()))
		{
			PlayerCharacterController->SetViewTargetWithBlend(PlayerCharacterController->GetPawn(), CameraBlendTime, EViewTargetBlendFunction::VTBlend_Linear);
		}
	}
}