#include "MyExample007_Notify_Fire.h"
#include "MyExample007_Character.h"

void UMyExample007_UAnim_Notify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
//	MY_LOG_WARNING(TEXT("UMyExample007_UAnim_Notify Notify"));

	if (auto* MyExample007_Character = Cast<AMyExample007_Character>(MeshComp->GetOwner()))
	{
		MyExample007_Character->AnimNotify_Fire();
	}
}

UMyExample007_AnimNotifyState_Example::UMyExample007_AnimNotifyState_Example() {

#if WITH_EDITORONLY_DATA
	NotifyColor = FColor::Yellow;
	bShouldFireInEditor = true;
#endif // WITH_EDITORONLY_DATA

	bIsNativeBranchingPoint = false; // disabled UAnimInstance::OnPlayMontageNotifyBegin/OnPlayMontageNotifyEnd 
}

void UMyExample007_AnimNotifyState_Example::NotifyBegin(USkeletalMeshComponent* MeshComp
													  , UAnimSequenceBase* Animation
													  , float TotalDuration
													  , const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	MY_LOG_WARNING(TEXT("AnimNotifyState_Example Begin"));
}

void UMyExample007_AnimNotifyState_Example::NotifyTick(USkeletalMeshComponent* MeshComp
													 , UAnimSequenceBase* Animation
													 , float FrameDeltaTime
													 , const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
//	MY_LOG_WARNING(TEXT("AnimNotifyState_Example Tick"));
}

void UMyExample007_AnimNotifyState_Example::NotifyEnd(USkeletalMeshComponent* MeshComp
													, UAnimSequenceBase* Animation
													, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	MY_LOG_WARNING(TEXT("AnimNotifyState_Example End"));
}