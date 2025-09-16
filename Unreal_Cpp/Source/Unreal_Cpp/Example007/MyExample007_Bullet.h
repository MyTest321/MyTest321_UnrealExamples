#pragma once

#include "CoreMinimal.h"
#include "MyExample007_Bullet.generated.h"

class UMyExample003_CubeMeshComponent;

UCLASS(ClassGroup = MyExample007)
class UNREAL_CPP_API AMyExample007_Bullet : public AActor {
	GENERATED_BODY()
public:	
	AMyExample007_Bullet();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UMyExample003_CubeMeshComponent> CubeComponent;

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 100.f;

	UPROPERTY(EditAnywhere)
	float Lifespan = 5.f;

	UPROPERTY(EditAnywhere)
	float SimPhysicTime = 3.f;

protected:
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(VisibleAnywhere, Transient)
	float _lifeTime = 0;
};
