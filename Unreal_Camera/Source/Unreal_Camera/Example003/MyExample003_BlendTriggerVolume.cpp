#include "MyExample003_BlendTriggerVolume.h"
#include "Components/BoxComponent.h"
#include "../Unreal_CameraCharacter.h"
#include "Camera/CameraActor.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

AMyExample003_BlendTriggerVolume::AMyExample003_BlendTriggerVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	MyCDO::CreateComponent(this, OverlapVolume);

//	MY_CDO_FINDER(CameraToFind_CameraActorClass, TEXT("/Script/CoreUObject.Class'/Script/CinematicCamera.CineCameraActor'"));
	MY_CDO_FINDER(CameraToFind_CameraActorClass, TEXT("/Script/Engine.Blueprint'/Game/ThirdPerson/Example003/BP_Example003_CameraActor'"));
}

void AMyExample003_BlendTriggerVolume::BeginPlay()
{
	Super::BeginPlay();
}

void AMyExample003_BlendTriggerVolume::NotifyActorBeginOverlap(AActor* HitResultActor)
{
	if (auto* PlayerCharacterCheck = Cast<AUnreal_CameraCharacter>(HitResultActor))
	{
		if (auto* PlayerCharacterController = Cast<APlayerController>(PlayerCharacterCheck->GetController()))
		{
			TArray<AActor*> FoundActors;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), CameraToFind_CameraActorClass, FoundActors);
			if (FoundActors.IsEmpty())
				return;

			PlayerCharacterController->SetViewTargetWithBlend(FoundActors[0], CameraBlendTime, EViewTargetBlendFunction::VTBlend_Linear);
		}
	}
}

void AMyExample003_BlendTriggerVolume::NotifyActorEndOverlap(AActor* HitResultActor)
{
	if (auto* PlayerCharacterCheck = Cast<AUnreal_CameraCharacter>(HitResultActor))
	{
		if (auto* PlayerCharacterController = Cast<APlayerController>(PlayerCharacterCheck->GetController()))
		{
			PlayerCharacterController->SetViewTargetWithBlend(PlayerCharacterController->GetPawn(), CameraBlendTime, EViewTargetBlendFunction::VTBlend_Linear);
		}
	}
}