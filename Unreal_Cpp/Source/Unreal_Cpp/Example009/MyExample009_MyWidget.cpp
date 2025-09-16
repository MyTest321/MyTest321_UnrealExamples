#include "MyExample009_MyWidget.h"
#include "MyExample009_MyListItemWidget.h"

UMyExample009_MyWidget::UMyExample009_MyWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bIsFocusable = true;
}

void UMyExample009_MyWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	MyButton->OnPressed.AddDynamic(this, &ThisClass::OnButtonPressed);
}

void UMyExample009_MyWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	_Count++;

	{
		FStringFormatOrderedArguments fmtArgs;
		fmtArgs.Add(_Count);
		FString str = FString::Format(TEXT("Count {0}"), fmtArgs);
		MyTextBlock->SetText(FText::FromString(str));
	}
}

void UMyExample009_MyWidget::OnButtonPressed()
{
	MY_LOG_WARNING(TEXT("OnButtonPressed"));

	if (MyListView)
	{
		auto* MyExample009_ListItemData = NewObject<UMyExample009_ListItemData>();
		MyExample009_ListItemData->testInt = _Count;

		MyListView->AddItem(MyExample009_ListItemData);
	}

	if (MyExample009_TestUIAnim)
	{
		PlayAnimation(MyExample009_TestUIAnim);
	}
}

void UMyExample009_MyWidget::BeginDestroy() {
	if (MyButton)
	{
		MyButton->OnPressed.RemoveAll(this);
	}
	Super::BeginDestroy();
}