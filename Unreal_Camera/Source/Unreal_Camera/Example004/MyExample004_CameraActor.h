#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "MyExample004_CameraActor.generated.h"

UCLASS()
class AMyExample004_CameraActor : public ACameraActor {
	GENERATED_BODY()
public:	
	AMyExample004_CameraActor();

protected:
	virtual void BeginPlay() override;
};
