#pragma once
#include "CoreMinimal.h"
#include <Animation/AnimNotifies/AnimNotify.h>
#include <Animation/AnimNotifies/AnimNotifyState.h>
#include "MyExample007_Notify_Fire.generated.h"

UCLASS(ClassGroup = MyExample007)
class UMyExample007_UAnim_Notify : public UAnimNotify {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	int TestInt = 0;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};

UCLASS(ClassGroup = MyExample007)
class UMyExample007_AnimNotifyState_Example : public UAnimNotifyState {
	GENERATED_BODY()
public:
	UMyExample007_AnimNotifyState_Example();
protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
