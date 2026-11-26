// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyFooGameGameMode.generated.h"

UCLASS(minimalapi)
class AMyFooGameGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AMyFooGameGameMode();
	
#if WITH_EDITOR
	static const FName kFolderPath;
#endif
};



