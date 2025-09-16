#include "MyGameUtil.h"

#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"

UWorld* MyGameUtil::CurWorld() {
	if (!GEngine)
	{
		return nullptr;
	}
	return GEngine->GetCurrentPlayWorld();
}

UGameInstance* MyGameUtil::GameInstance()
{
	auto* World = CurWorld();
	if (!World)
	{
		return nullptr;
	}
	return World->GetGameInstance();
}

AGameModeBase* MyGameUtil::CurGameMode()
{
	auto* World = CurWorld();
	if (!IsValid(World))
	{
		return nullptr;
	}
	return World->GetAuthGameMode();
}

void MyGameUtil::SetShowMouseCursor(bool bShow)
{
	if (auto* p = CurWorld()->GetFirstPlayerController())
	{
		p->SetShowMouseCursor(bShow);
	}
}

void MyGameUtil::GetAllActorsWithTag(TArray<AActor*>& OutActors, const FName& Tag) {
	UGameplayStatics::GetAllActorsWithTag(MyGameUtil::CurWorld(), Tag, OutActors);
}
