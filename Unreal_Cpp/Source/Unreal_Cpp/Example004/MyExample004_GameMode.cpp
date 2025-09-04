#include "MyExample004_GameMode.h"

#include "UObject/ConstructorHelpers.h"
#include "MyExample004_PlayerController.h"
#include "MyExample004_Pawn.h"

AMyExample004_GameMode::AMyExample004_GameMode() {
	GameSessionClass = nullptr;
	PlayerStateClass = nullptr;
	SpectatorClass	 = nullptr;
	HUDClass		 = nullptr;

//	PlayerControllerClass = nullptr;
//	PlayerControllerClass = AMyExample004_PlayerController::StaticClass();
	MY_CDO_FINDER(PlayerControllerClass, TEXT("Blueprint'/Game/ThirdPerson/Blueprints/MyExample004/BP_MyExample004_PlayerController'"));

//	DefaultPawnClass = nullptr;
	DefaultPawnClass = AMyExample004_Pawn::StaticClass();
//	MY_CDO_FINDER(DefaultPawnClass, TEXT("Blueprint'/Game/ThirdPerson/Blueprints/MyExample004/BP_MyExample004_Pawn'"));
}

void AMyExample004_GameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) {
	Super::InitGame(MapName, Options, ErrorMessage);
	MY_LOG_WARNING(TEXT("AMyExample004_GameMode::InitGame: MapName={}\nOptions={}\nErrorMessage={}"), MapName, Options, ErrorMessage);
}

void AMyExample004_GameMode::InitGameState() {
	Super::InitGameState();
	MY_LOG_WARNING(TEXT("AMyExample004_GameMode::InitGameState()"));
}

void AMyExample004_GameMode::StartPlay() {
	Super::StartPlay();
	MY_LOG_WARNING(TEXT("AMyExample004_GameMode::StartPlay()"));
}
