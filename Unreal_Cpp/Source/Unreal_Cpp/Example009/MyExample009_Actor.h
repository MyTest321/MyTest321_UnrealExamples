#pragma once

#include "CoreMinimal.h"
#include "MyExample009_Actor.generated.h"

class UWidgetComponent;

UCLASS()
class UNREAL_CPP_API AMyExample009_Actor : public AActor {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> WidgetComponentClass;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidgetComponent> WidgetComponent;

	AMyExample009_Actor();
};
