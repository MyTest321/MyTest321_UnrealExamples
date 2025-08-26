#include "MyExample003_GunComponent.h"
#include "MyExample003_Actor.h"
#include "MyExample003_Bullet.h"

UMyExample003_GunComponent::UMyExample003_GunComponent() {
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 1.f;

	SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
}

void UMyExample003_GunComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UWorld* World = GetWorld();
	if (!World)
		return;

	UClass*	Cls = nullptr;

	auto* owner = GetOwner();
	FVector SpawnLocation = owner->GetActorLocation();
	FRotator SpawnRotation = owner->GetActorRotation();
	if (auto* MyExample003_Actor = Cast<AMyExample003_Actor>(owner)) {
		Cls = MyExample003_Actor->BulletToSpawnClass.Get();
	}
	else {
		Cls = AMyExample003_Bullet::StaticClass();
	}

	if (Cls) {
		World->SpawnActor(Cls, &SpawnLocation, &SpawnRotation); // GetWorld()->SpawnActor<AMyExample003_Bullet>(Cls, SpawnLocation, SpawnRotation);
	}
}
