#include "MyExample009_PlayerController.h"
#include "MyExample009_MyWidget.h"
#include "MyExample009_NavigationConfig.h"

AMyExample009_PlayerController::AMyExample009_PlayerController()
{
	PrimaryActorTick.bCanEverTick = false;
	MY_CDO_FINDER(MyWidgetClass, TEXT("WidgetBlueprint'/Game/ThirdPerson/Blueprints/MyExample009/WBP_MyExample009_MyWidget'"));
}

void AMyExample009_PlayerController::BeginPlay() {
	Super::BeginPlay();

	CreateMyWidget();
}

void AMyExample009_PlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	SetShowMouseCursor(true);

	FMyExample009_NavigationConfig::s_Init(this);
}

void AMyExample009_PlayerController::CreateMyWidget()
{
	if (!MyWidgetClass)
	{
		MY_LOG_ERROR(TEXT("MyWidgetClass is nullptr"));
		return;
	}

	MyWidget = CreateWidget<UMyExample009_MyWidget>(this, MyWidgetClass);

	if (!MyWidget)
	{
		MY_LOG_ERROR(TEXT("CreateWidget"));
		return;
	}

	MyWidget->AddToViewport();
}