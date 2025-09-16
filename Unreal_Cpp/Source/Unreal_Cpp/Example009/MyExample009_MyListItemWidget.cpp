#include "MyExample009_MyListItemWidget.h"

void UMyExample009_MyListItemWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	auto* item = Cast<UMyExample009_ListItemData>(ListItemObject);
	if (!item)
	{
		MY_LOG_ERROR(TEXT("Error Cast UMyExample009_ListItemData"));
		return;
	}

	FString str = MyFormat(TEXT("ListItem {}"), item->testInt);
	MyItemText->SetText(FText::FromString(str));
}

