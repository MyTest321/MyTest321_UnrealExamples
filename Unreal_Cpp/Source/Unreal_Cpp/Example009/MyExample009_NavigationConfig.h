#pragma once

#include <Framework/Application/NavigationConfig.h>

class FMyExample009_NavigationConfig : public FNavigationConfig {
public:
	using ThisClass = FMyExample009_NavigationConfig;
	using Super = FNavigationConfig;

	virtual EUINavigation GetNavigationDirectionFromKey(const FKeyEvent& InKeyEvent) const override;
	virtual EUINavigation GetNavigationDirectionFromAnalog(const FAnalogInputEvent& InAnalogEvent) override;
	virtual EUINavigationAction GetNavigationActionFromKey(const FKeyEvent& InKeyEvent) const override;

	virtual void OnNavigationChangedFocus(TSharedPtr<SWidget> OldWidget, TSharedPtr<SWidget> NewWidget, FFocusEvent FocusEvent) override;

	static void s_Init(APlayerController* PC);

private:
	struct MyKeyMap;

	void _InitActionMap(APlayerController* PC);

	static FInputActionKeyMapping* s_FindInputAction(UPlayerInput* Input, FName ActionName);

	TMap<FName, EUINavigationAction> _KeyToActionMap;
	TMap<FName, EUINavigation>		 _KeyToDirectionMap;
	TMap<FName, FName>				 _KeyToPlayerControllerMap;
};