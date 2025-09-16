#include "MyExample007_GameMode.h"
#include "MyExample007_PlayerController.h"
#include "MyExample007_Character.h"

AMyExample007_GameMode::AMyExample007_GameMode() {
//	PlayerControllerClass = AMyExample007_PlayerController::StaticClass();
	MY_CDO_FINDER(PlayerControllerClass, TEXT("Blueprint'/Game/ThirdPerson/Blueprints/MyExample007/BP_MyExample007_PlayerController'"));

//	DefaultPawnClass      = AMyExample007_Character::StaticClass();
	MY_CDO_FINDER(DefaultPawnClass, TEXT("Blueprint'/Game/ThirdPerson/Blueprints/MyExample007/BP_MyExample007_Character'"));
}