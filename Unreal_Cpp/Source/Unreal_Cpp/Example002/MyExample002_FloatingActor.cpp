#include "MyExample002_FloatingActor.h"

AMyExample002_FloatingActor::AMyExample002_FloatingActor() {
	PrimaryActorTick.bCanEverTick = true;

	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UStaticMeshComponent"));
	VisualMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAssetObj(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));

	if (CubeVisualAssetObj.Succeeded()) {
		VisualMesh->SetStaticMesh(CubeVisualAssetObj.Object);
		VisualMesh->SetRelativeLocation(FVector::Zero());
	}
}

void AMyExample002_FloatingActor::BeginPlay() {
	Super::BeginPlay();
}

void AMyExample002_FloatingActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

#if 0
	FRotator NewRotation = GetActorRotation();
	float DeltaRotation = DeltaTime * RotateSpeed;
	NewRotation.Yaw += DeltaRotation;
	SetActorRotation(NewRotation);
#else
	FVector	 NewLocation = GetActorLocation();
	FRotator NewRotation = GetActorRotation();

	float RunningTime = GetGameTimeSinceCreation();
	float DeltaHeight = (FMath::Sin((RunningTime + DeltaTime * 2 * 3.14f * FloatingSpeedRate)) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * FloatingDistance;

	float DeltaRotation = DeltaTime * RotateSpeed;
	NewRotation.Yaw += DeltaRotation;
	SetActorLocationAndRotation(NewLocation, NewRotation);
#endif
}

