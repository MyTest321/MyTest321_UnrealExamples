#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyExample009_MyWidget.generated.h"

class FObjectInitializer;

class UTextBlock;
class UButton;
class UListView;
class UWidgetAnimation;

UCLASS()
class UNREAL_CPP_API UMyExample009_MyWidget : public UUserWidget {
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, Transient, meta = (BindWidget)) TObjectPtr<UTextBlock>	MyTextBlock;
	UPROPERTY(EditAnywhere, Transient, meta = (BindWidget)) TObjectPtr<UButton>		MyButton;
	UPROPERTY(EditAnywhere, Transient, meta = (BindWidget)) TObjectPtr<UListView>	MyListView;

	UPROPERTY(EditAnywhere, Transient, meta = (BindWidgetAnim)) TObjectPtr<UWidgetAnimation>	MyExample009_TestUIAnim;

	UMyExample009_MyWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void BeginDestroy() override;

private:
	UFUNCTION()
	void OnButtonPressed();

	int _Count = 0;
};
