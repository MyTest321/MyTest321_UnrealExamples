#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyExample002_FloatingActor.generated.h"

UCLASS()
class UNREAL_CPP_API AMyExample002_FloatingActor : public AActor {
	GENERATED_BODY()
public:	
	AMyExample002_FloatingActor();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* VisualMesh;

	UPROPERTY(EditAnywhere)
	float RotateSpeed = 20.f;

	UPROPERTY(EditAnywhere)
	float FloatingDistance = 20.f;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", ClampMax = "10"))
	float FloatingSpeedRate = 1.f;

protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;
};
