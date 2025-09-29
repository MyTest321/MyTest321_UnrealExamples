// Copyright Epic Games, Inc. All Rights Reserved.

#include "Unreal_CameraGameMode.h"
#include "Unreal_CameraCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUnreal_CameraGameMode::AUnreal_CameraGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
