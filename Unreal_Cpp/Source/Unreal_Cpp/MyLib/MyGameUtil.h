#pragma once

#include "CoreMinimal.h"

class AGameModeBase;
class UGameInstance;
class UWorld;
class FName;

struct MyGameUtil {
	MyGameUtil() = delete;

	static UWorld* CurWorld();

	static UGameInstance* GameInstance();
	template <class GAME_INSTANCE_TYPE> static inline GAME_INSTANCE_TYPE* GameInstance();

	AGameModeBase* CurGameMode();
	template <class GAME_MODE_TYPE> static inline GAME_MODE_TYPE* CurGameMode();

	static void SetShowMouseCursor(bool bShow);

	static void GetAllActorsWithTag(TArray<AActor*>& OutActors, const FName& Tag);
};

template <class GAME_INSTANCE_TYPE> inline
GAME_INSTANCE_TYPE* MyGameUtil::GameInstance()
{
	auto* Inst = MyGameUtil::GameInstance();
	if (!IsValid(Inst))
	{
		return nullptr;
	}
	return CastChecked<GAME_INSTANCE_TYPE>(Inst);
}

template <class GAME_MODE_TYPE> inline
GAME_MODE_TYPE* MyGameUtil::CurGameMode() {
	auto* GameMode = MyGameUtil::CurGameMode();
	if (!IsValid(GameMode)) {
		return nullptr;
	}
	return CastChecked<GAME_MODE_TYPE>(GameMode);
}