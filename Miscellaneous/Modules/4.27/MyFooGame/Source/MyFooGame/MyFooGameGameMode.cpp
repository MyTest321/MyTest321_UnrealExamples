// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyFooGameGameMode.h"
#include "MyFooGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

#if WITH_EDITOR
	const FName AMyFooGameGameMode::kFolderPath = FName("#_MyGame");
#endif

AMyFooGameGameMode::AMyFooGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
