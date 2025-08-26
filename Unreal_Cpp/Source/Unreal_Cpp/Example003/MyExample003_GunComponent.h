#pragma once

#include "CoreMinimal.h"
#include "MyExample003_CubeMeshComponent.h"
#include "MyExample003_GunComponent.generated.h"

UCLASS(ClassGroup = MyExample003, meta = (BlueprintSpawnableComponent))
class UNREAL_CPP_API UMyExample003_GunComponent : public UMyExample003_CubeMeshComponent {
	GENERATED_BODY()
public:	
	UMyExample003_GunComponent();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
