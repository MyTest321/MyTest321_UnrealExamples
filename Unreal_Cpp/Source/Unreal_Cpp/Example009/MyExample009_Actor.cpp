#include "MyExample009_Actor.h"
#include <Components/WidgetComponent.h>

AMyExample009_Actor::AMyExample009_Actor() {
	PrimaryActorTick.bCanEverTick = false;

	MyActorUtil::SetRootComponent_UMyExample003_CubeMeshComponent(this);
	RootComponent->SetRelativeScale3D(FVector::OneVector);

	MY_CDO_FINDER(WidgetComponentClass, TEXT("WidgetBlueprint'/Game/ThirdPerson/Blueprints/MyExample009/WBP_MyExample009_WorldSpaceWidget'"));
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("MyWidgetComponent"));
	WidgetComponent->SetWidgetClass(WidgetComponentClass);

	WidgetComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	WidgetComponent->SetRelativeLocation(FVector(0, 0, 130));
}
