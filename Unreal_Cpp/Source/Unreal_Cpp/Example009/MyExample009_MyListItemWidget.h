#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "MyExample009_MyListItemWidget.generated.h"

UCLASS()
class UMyExample009_ListItemData : public UObject {
	GENERATED_BODY()
public:
	int testInt = 0;
};


UCLASS()
class UNREAL_CPP_API UMyExample009_MyListItemWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Transient, meta=(BindWidget)) UTextBlock* MyItemText = nullptr;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
};
