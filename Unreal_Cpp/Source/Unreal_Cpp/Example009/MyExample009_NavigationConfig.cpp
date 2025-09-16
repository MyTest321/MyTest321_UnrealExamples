#include "MyExample009_NavigationConfig.h"

struct FMyExample009_NavigationConfig::MyKeyMap
{
	TMap<FName, EUINavigationAction>	ActionMap;
	TMap<FName, EUINavigation>			DirectionMap;

	MyKeyMap()
	{
		DirectionMap.Add("UI_Up",		EUINavigation::Up);
		DirectionMap.Add("UI_Down",		EUINavigation::Down);
		DirectionMap.Add("UI_Left",		EUINavigation::Left);
		DirectionMap.Add("UI_Right",	EUINavigation::Right);
		DirectionMap.Add("UI_Prev",		EUINavigation::Previous);
		DirectionMap.Add("UI_Next",		EUINavigation::Next);

		ActionMap.Add("UI_Accept",	EUINavigationAction::Accept);
		ActionMap.Add("UI_Back",	EUINavigationAction::Back);
	}
};

void FMyExample009_NavigationConfig::s_Init(APlayerController* PC)
{
	TSharedRef<FMyExample009_NavigationConfig> NavConfig = MakeShareable(new FMyExample009_NavigationConfig());
	NavConfig->_InitActionMap(PC);

	auto& app = FSlateApplication::Get();
	app.SetNavigationConfig(MoveTemp(NavConfig));
}

void FMyExample009_NavigationConfig::_InitActionMap(APlayerController* PC)
{
	static MyKeyMap s_KeyMap;

	if (!PC || !PC->PlayerInput) return;

	for (auto& It : PC->PlayerInput->ActionMappings)
	{
		if (EUINavigationAction* eUINavigationAction = s_KeyMap.ActionMap.Find(It.ActionName))
		{
			_KeyToActionMap.Add(It.Key.GetFName(), *eUINavigationAction);
		}
		if (EUINavigation* eUINavigation = s_KeyMap.DirectionMap.Find(It.ActionName))
		{
			_KeyToDirectionMap.Add(It.Key.GetFName(), *eUINavigation);
		}

		if (It.ActionName.ToString().StartsWith("UI_"))
		{
			_KeyToPlayerControllerMap.Add(It.Key.GetFName(), It.ActionName);
		}
	}

#if WITH_EDITOR
	for (auto& It : s_KeyMap.ActionMap)
	{
		if (!s_FindInputAction(PC->PlayerInput, It.Key))
		{
			MY_LOG_WARNING(TEXT("UINavigation missing Action {}"), It.Key);
		}
	}
	for (auto& It : s_KeyMap.DirectionMap)
	{
		if (!s_FindInputAction(PC->PlayerInput, It.Key))
		{
			MY_LOG_WARNING(TEXT("UINavigation missing Action {}"), It.Key);
		}
	}
#endif
}

FInputActionKeyMapping* FMyExample009_NavigationConfig::s_FindInputAction(UPlayerInput* Input, FName ActionName) {
	if (!Input)
		return nullptr;

	for (auto& E : Input->ActionMappings) {
		if (E.ActionName == ActionName)
			return &E;
	}
	return nullptr;
}

EUINavigation FMyExample009_NavigationConfig::GetNavigationDirectionFromKey(const FKeyEvent& InKeyEvent) const
{
	auto key = InKeyEvent.GetKey().GetFName();
	if (auto* dir = _KeyToDirectionMap.Find(key))
	{
		MY_LOG_INFO(TEXT("GetNavigationDirectionFromKey {} -> {}"), key, MyEnum::ToFName(*dir));
		return *dir;
	}

	return EUINavigation::Invalid;
}

EUINavigationAction FMyExample009_NavigationConfig::GetNavigationActionFromKey(const FKeyEvent& InKeyEvent) const
{
	auto key = InKeyEvent.GetKey().GetFName();
	if (auto* act = _KeyToActionMap.Find(key))
	{
		MY_LOG_INFO(TEXT("GetNavigationActionFromKey {} -> {}"), key, MyEnum::ToFName(*act));
		return *act;
	}
	return EUINavigationAction::Invalid;
}


EUINavigation FMyExample009_NavigationConfig::GetNavigationDirectionFromAnalog(const FAnalogInputEvent& InAnalogEvent)
{
	return Super::GetNavigationDirectionFromAnalog(InAnalogEvent);
}

void FMyExample009_NavigationConfig::OnNavigationChangedFocus(TSharedPtr<SWidget> OldWidget, TSharedPtr<SWidget> NewWidget, FFocusEvent FocusEvent)
{
	Super::OnNavigationChangedFocus(OldWidget, NewWidget, FocusEvent);
}
