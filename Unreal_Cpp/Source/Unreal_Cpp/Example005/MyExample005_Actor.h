#pragma once

#include "Animation/SkeletalMeshActor.h"
#include "MyExample005_Actor.generated.h"

UCLASS()
class UNREAL_CPP_API AMyExample005_Actor : public ASkeletalMeshActor {
	GENERATED_BODY()
public:	
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", ClampMax = "1"))
	float TestBlend = 0.5f;
};
