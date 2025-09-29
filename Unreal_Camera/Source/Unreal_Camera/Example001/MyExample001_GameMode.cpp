#include "MyExample001_GameMode.h"
#include "MyExample001_Character.h"

AMyExample001_GameMode::AMyExample001_GameMode() {
	MY_CDO_FINDER(DefaultPawnClass, TEXT("/Script/Engine.Blueprint'/Game/ThirdPerson/Example001/BP_MyExample001_Character'"));
}