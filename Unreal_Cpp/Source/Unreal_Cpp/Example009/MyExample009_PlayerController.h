#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyExample009_PlayerController.generated.h"

class UMyExample009_MyWidget;

UCLASS()
class UNREAL_CPP_API AMyExample009_PlayerController : public APlayerController {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UMyExample009_MyWidget> MyWidgetClass;

	UPROPERTY(VisibleAnywhere, Transient)
	TObjectPtr<UMyExample009_MyWidget> MyWidget;

	AMyExample009_PlayerController();

	void CreateMyWidget();

protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
};
