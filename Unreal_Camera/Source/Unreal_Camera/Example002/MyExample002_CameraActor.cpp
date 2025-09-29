#include "MyExample002_CameraActor.h"
#include "../Unreal_CameraCharacter.h"

AMyExample002_CameraActor::AMyExample002_CameraActor() {
	PrimaryActorTick.bCanEverTick = false;

	MyCDO::CreateComponent(RootComponent, BoxComp);
	BoxComp->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
}

void AMyExample002_CameraActor::BeginPlay()
{
	Super::BeginPlay();

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnComponentBeginOverlap_Box);
	BoxComp->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnComponentEndOverlap_Box);

	for (auto& Box : BoxComps)
	{
		if (Box.IsNull())
		{
			continue;
		}
		Box->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnComponentBeginOverlap_Box);
		Box->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnComponentEndOverlap_Box);
	}
}

void AMyExample002_CameraActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	EnsureComponentAttachments();
}

void AMyExample002_CameraActor::EnsureComponentAttachments()
{
	if (!RootComponent)
		return;

	for (auto& Comp : BoxComps)
	{
		if (!Comp) continue;

		if (Comp->GetAttachParent() != RootComponent)
		{
			Comp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		}

		if (!Comp->IsRegistered())
		{
			Comp->RegisterComponent();
		}
	}
}

bool AMyExample002_CameraActor::IsMyCharacterOverlappingBox(AUnreal_CameraCharacter* Character)
{
	if (BoxComp)
	{
		if (BoxComp->IsOverlappingActor(Character))
		{
			return true;
		}
	}

	for (auto& Comp : BoxComps)
	{
		if (!Comp) continue;
		if (Comp->IsOverlappingActor(Character))
		{
			return true;
		}
	}

	return false;
}

void AMyExample002_CameraActor::OnComponentBeginOverlap_Box(UPrimitiveComponent* OverlappedComponent, 
															AActor* OtherActor, 
															UPrimitiveComponent* OtherComp, 
															int32 OtherBodyIndex, 
															bool bFromSweep, 
															const FHitResult& SweepResult)
{
	if (!OtherActor)
		return;
	if (OtherComp->IsA(BoxComp.GetClass()))
		return;
	if (OtherActor == this)
		return;
	if (!OtherComp)
		return;

	MY_LOG_WARNING(TEXT("OnComponentBeginOverlap_Box with: {}"), *OtherActor->GetName());

	if (auto* PlayerCharacterCheck = Cast<AUnreal_CameraCharacter>(OtherActor))
	{
		if (auto* PlayerCharacterController = Cast<APlayerController>(PlayerCharacterCheck->GetController()))
		{
			PlayerCharacterController->SetViewTargetWithBlend(this, CameraBlendTime, EViewTargetBlendFunction::VTBlend_Linear);
		}
	}
}

void AMyExample002_CameraActor::OnComponentEndOverlap_Box(UPrimitiveComponent* OverlappedComponent, 
														  AActor* OtherActor, 
														  UPrimitiveComponent* OtherComp, 
														  int32 OtherBodyIndex)
{
	if (!OtherActor)
		return;
	if (OtherComp->IsA(BoxComp.GetClass()))
		return;
	if (OtherActor == this)
		return;
    if (!OtherComp)
		return;

	MY_LOG_WARNING(TEXT("OnComponentEndOverlap_Box with: {}"), *OtherActor->GetName());

	if (auto* PlayerCharacterCheck = Cast<AUnreal_CameraCharacter>(OtherActor))
	{
		if (auto* PlayerCharacterController = Cast<APlayerController>(PlayerCharacterCheck->GetController()))
		{
			if (!IsMyCharacterOverlappingBox(PlayerCharacterCheck))
			{
				PlayerCharacterController->SetViewTargetWithBlend(PlayerCharacterController->GetPawn(), CameraBlendTime, EViewTargetBlendFunction::VTBlend_Linear);
			}
		}
	}
}

void AMyExample002_CameraActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (BoxComp)
    {
		BoxComp->OnComponentBeginOverlap.RemoveAll(this);
		BoxComp->OnComponentEndOverlap.RemoveAll(this);
    }

	for (auto& Box : BoxComps)
	{
		if (Box.IsNull())
		{
			continue;
		}
		Box->OnComponentBeginOverlap.RemoveAll(this);
		Box->OnComponentEndOverlap.RemoveAll(this);
	}

    Super::EndPlay(EndPlayReason);
}