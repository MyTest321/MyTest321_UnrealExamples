// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyFooGame.h"
#include "Modules/ModuleManager.h"
#include "MyCore/Base/MyConsole.h"

#if WITH_EDITOR
	#include "Interfaces/IMainFrameModule.h"
#endif // WITH_EDITOR

#define LOCTEXT_NAMESPACE "MyFooGameModuleImpl"

class MyFooGameModuleImpl : public IModuleInterface
{
	using ThisClass = MyFooGameModuleImpl;

public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
#if WITH_EDITOR
	void OnEditorStartup();
	void OnEditorMainFrameStartup();
#endif // WITH_EDITOR
};

inline void MyFooGameModuleImpl::StartupModule()
{
#if WITH_EDITOR
	OnEditorStartup();
#endif // WITH_EDITOR
}

#if WITH_EDITOR
void MyFooGameModuleImpl::OnEditorStartup()
{
	IMainFrameModule& MainFrameModule = IMainFrameModule::Get();
	if (MainFrameModule.IsWindowInitialized())
	{
		OnEditorMainFrameStartup();
	}
	else
	{
		MainFrameModule.OnMainFrameCreationFinished().AddLambda(
			[this](TSharedPtr<SWindow> InRootWindow, bool bIsRunningStartupDialog) {
				OnEditorMainFrameStartup();
			}
        );
	}
}

void MyFooGameModuleImpl::OnEditorMainFrameStartup()
{
	MyConsole::SetVar(TEXT("t.MaxFPS"), 60); // limit the fps to avoid burning my GPU in editor during development
	MyConsole::EditorCmd(TEXT("stat fps")); // show fps
}
#endif // WITH_EDITOR

void MyFooGameModuleImpl::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE

//IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, MyFooGame, "MyFooGame" );
IMPLEMENT_PRIMARY_GAME_MODULE(MyFooGameModuleImpl, MyFooGame, "MyFooGame");
 