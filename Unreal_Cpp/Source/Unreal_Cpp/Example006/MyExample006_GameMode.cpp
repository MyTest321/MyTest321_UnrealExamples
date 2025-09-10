#include "MyExample006_GameMode.h"
#include "MyExample006_PlayerController.h"
#include "MyExample006_Character.h"

AMyExample006_GameMode::AMyExample006_GameMode() {
//	PlayerControllerClass = AMyExample006_PlayerController::StaticClass();
	MY_CDO_FINDER(PlayerControllerClass, TEXT("Blueprint'/Game/ThirdPerson/Blueprints/MyExample006/BP_MyExample006_PlayerController'"));

//	DefaultPawnClass      = AMyExample006_Character::StaticClass();
	MY_CDO_FINDER(DefaultPawnClass, TEXT("Blueprint'/Game/ThirdPerson/Blueprints/MyExample006/BP_MyExample006_Character'"));
}