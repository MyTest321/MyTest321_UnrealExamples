#include "MyExample009_GameMode.h"
#include "MyExample009_PlayerController.h"

AMyExample009_GameMode::AMyExample009_GameMode() {
	PlayerControllerClass = AMyExample009_PlayerController::StaticClass();
}