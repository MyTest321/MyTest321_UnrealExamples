#pragma once

#include "CoreMinimal.h"
#include "MyExample003_RotateComponent.generated.h"

UCLASS(ClassGroup = MyExample003, meta = (BlueprintSpawnableComponent))
class UNREAL_CPP_API UMyExample003_RotateComponent : public UStaticMeshComponent {
	GENERATED_BODY()
public:	
	UMyExample003_RotateComponent();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(Category = MyExample003, EditAnywhere)
	float RotateSpeed = 100.f;
};
