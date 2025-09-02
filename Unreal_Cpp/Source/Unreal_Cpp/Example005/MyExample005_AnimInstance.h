#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyExample005_AnimInstance.generated.h"

UCLASS()
class UNREAL_CPP_API UMyExample005_AnimInstance : public UAnimInstance {
	GENERATED_BODY()
public:	
	UMyExample005_AnimInstance();

    UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0", ClampMax = "1"))
	float TestBlend = 0.5f;

    virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
