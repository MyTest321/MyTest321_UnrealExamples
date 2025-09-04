#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyExample004_GameMode.generated.h"

UCLASS()
class UNREAL_CPP_API AMyExample004_GameMode : public AGameModeBase {
	GENERATED_BODY()
public:
	AMyExample004_GameMode();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) final;
	virtual void InitGameState() final;
	virtual void StartPlay() final;
};
