#include "MyExample003_RotateComponent.h"

UMyExample003_RotateComponent::UMyExample003_RotateComponent() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UMyExample003_RotateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	auto* Actor = GetOwner();
	FRotator Rot = Actor->GetActorRotation();
	Rot.Yaw += RotateSpeed * DeltaTime;
	Actor->SetActorRotation(Rot);
}
