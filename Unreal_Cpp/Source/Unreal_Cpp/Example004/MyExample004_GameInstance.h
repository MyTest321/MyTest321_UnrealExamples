#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyExample004_GameInstance.generated.h"

UCLASS()
class UNREAL_CPP_API UMyExample004_GameInstance : public UGameInstance {
	GENERATED_BODY()
public:
	virtual void OnStart() final;
};
