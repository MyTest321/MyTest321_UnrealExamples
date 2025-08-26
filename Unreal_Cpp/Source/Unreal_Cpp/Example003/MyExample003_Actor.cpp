#include "MyExample003_Actor.h"

#include "MyExample003_RotateComponent.h"
#include "Components/BillboardComponent.h"
#include "MyExample003_GunComponent.h"

AMyExample003_Actor::AMyExample003_Actor() {
	PrimaryActorTick.bCanEverTick = false;

	MyActorUtil::SetRootComponent_UBillboardComponent(this);
	MyCDO::CreateComponent(this, RotateComponent);
}

void AMyExample003_Actor::BeginPlay() {
	Super::BeginPlay();

#if 0
	GunComponent = NewObject<UMyExample003_GunComponent>(this);
	this->AddInstanceComponent(GunComponent);
	GunComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	GunComponent->RegisterComponent();
#else
	GunComponent = MyActorUtil::NewComponent<UMyExample003_GunComponent>(this, 
		GunDefaultClass ? GunDefaultClass.Get() : UMyExample003_GunComponent::StaticClass());
#endif

}