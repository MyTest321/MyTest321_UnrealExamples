#pragma once

#include "CoreMinimal.h"
#include "MyExample003_Actor.generated.h"

class UMyExample003_RotateComponent;

UCLASS()
class UNREAL_CPP_API AMyExample003_Actor : public AActor {
	GENERATED_BODY()
public:	
	AMyExample003_Actor();

	UPROPERTY(VisibleAnywhere)				TObjectPtr<UMyExample003_RotateComponent> RotateComponent;
	UPROPERTY(VisibleAnywhere, Transient)	TObjectPtr<class UMyExample003_GunComponent> GunComponent;

	UPROPERTY(Category = "MyExample003", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UMyExample003_GunComponent> GunDefaultClass;

	UPROPERTY(Category = "MyExample003", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AMyExample003_Bullet> BulletToSpawnClass;

protected:
	virtual void BeginPlay() override;
};
