#pragma once

#include "CoreMinimal.h"
#include "MyExample003_Bullet.generated.h"

UCLASS(ClassGroup = MyExample003)
class UNREAL_CPP_API AMyExample003_Bullet : public AActor {
	GENERATED_BODY()
public:	
	AMyExample003_Bullet();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UMyExample003_CubeMeshComponent> CubeComponent;

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 100;

protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;
};
