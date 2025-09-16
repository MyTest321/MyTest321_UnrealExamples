#include "MyExample007_Bullet.h"
#include "../Example003/MyExample003_CubeMeshComponent.h"

AMyExample007_Bullet::AMyExample007_Bullet()
{
	PrimaryActorTick.bCanEverTick = true;

	CubeComponent = MyActorUtil::SetRootComponent_UMyExample003_CubeMeshComponent(this);
	RootComponent->SetRelativeScale3D(FVector::OneVector * 0.25f);

	RootComponent->SetMobility(EComponentMobility::Movable);
}

void AMyExample007_Bullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	_lifeTime += DeltaTime;

	if (_lifeTime > Lifespan)
	{
		Destroy();
		return;
	}

	if (_lifeTime > SimPhysicTime && CubeComponent)
	{
		CubeComponent->SetSimulatePhysics(true);
		return;
	}

	auto Loc = GetActorLocation();
	Loc += GetActorForwardVector() * (MoveSpeed * DeltaTime);
	SetActorLocation(Loc);
}

