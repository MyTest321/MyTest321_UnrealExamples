// Copyright Epic Games, Inc. All Rights Reserved.

#include "Unreal_CppGameMode.h"
#include "Unreal_CppCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUnreal_CppGameMode::AUnreal_CppGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
