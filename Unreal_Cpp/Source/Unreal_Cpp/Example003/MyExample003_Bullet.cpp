#include "MyExample003_Bullet.h"

AMyExample003_Bullet::AMyExample003_Bullet() {
	PrimaryActorTick.bCanEverTick = true;

	MyActorUtil::SetRootComponent_UMyExample003_CubeMeshComponent(this);
	RootComponent->SetRelativeScale3D(FVector(0.5f, 0.25f, 0.25f));
}

void AMyExample003_Bullet::BeginPlay()
{
	Super::BeginPlay();
}

void AMyExample003_Bullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto NewLoc = GetActorLocation();
	NewLoc += GetActorForwardVector() * (MoveSpeed * DeltaTime);
	SetActorLocation(NewLoc);
}

