#include "MyExample004_Pawn.h"

AMyExample004_Pawn::AMyExample004_Pawn() {
	PrimaryActorTick.bCanEverTick = false;
	MyActorUtil::SetRootComponent_UMyExample003_CubeMeshComponent(this);
}

void AMyExample004_Pawn::BeginPlay() {
	SetActorLocation(FVector::Zero());
}
	