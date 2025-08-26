#include "MyExample003_CubeMeshComponent.h"

UMyExample003_CubeMeshComponent::UMyExample003_CubeMeshComponent() {
	PrimaryComponentTick.bCanEverTick = false;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> AssetObj(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (AssetObj.Succeeded()) {
		SetStaticMesh(AssetObj.Object);
		SetRelativeLocation(FVector::Zero());
	}
}
