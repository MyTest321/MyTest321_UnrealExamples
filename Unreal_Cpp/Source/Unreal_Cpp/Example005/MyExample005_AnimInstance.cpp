#include "MyExample005_AnimInstance.h"
#include "MyExample005_Actor.h"

UMyExample005_AnimInstance::UMyExample005_AnimInstance() {
}

void UMyExample005_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    auto* SkelMeshComp = GetSkelMeshComponent();
	if (!SkelMeshComp) return;

	if (auto* MyExample005_Actor = Cast<AMyExample005_Actor>(SkelMeshComp->GetOwner())) {
        TestBlend = MyExample005_Actor->TestBlend;
    }
}