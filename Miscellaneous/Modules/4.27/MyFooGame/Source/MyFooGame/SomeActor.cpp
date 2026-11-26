#include "SomeActor.h"
#include "MyFooGameGameMode.h"

#include "FooBar/src/NicknamedActor.h"
#include "MyTest/src/MyTestSimpleActor.h"

ASomeActor::ASomeActor() {
	PrimaryActorTick.bCanEverTick = false;

	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UStaticMeshComponent"));
	VisualMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAssetObj(TEXT("StaticMesh'/Game/Geometry/Meshes/1M_Cube.1M_Cube'"));

	if (CubeVisualAssetObj.Succeeded()) {
		VisualMesh->SetStaticMesh(CubeVisualAssetObj.Object);
		VisualMesh->SetRelativeLocation(FVector::ZeroVector);
	}
	
	if (!NicknamedActorClass) {
		NicknamedActorClass = ANicknamedActor::StaticClass();
	}
	if (!MyTestSimpleActorClass) {
		MyTestSimpleActorClass = AMyTestSimpleActor::StaticClass();
	}
}

void ASomeActor::BeginPlay() {
	Super::BeginPlay();

	test_SpawnNickedActor();
	test_SpawnMyTestSimpleActor();
	
#if WITH_EDITOR
	this->SetFolderPath(AMyFooGameGameMode::kFolderPath);
#endif // WITH_EDITOR
}

void ASomeActor::test_SpawnNickedActor()
{
	UWorld* World = GetWorld();
	if (!World)
		return;
	
	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = GetActorRotation();
	
	UClass*	Cls = nullptr;
	auto* NewNickedActor = World->SpawnActor<ANicknamedActor>(NicknamedActorClass, SpawnLocation, SpawnRotation);
	if (NewNickedActor)
	{
		NewNickedActor->SayNickname();
#if WITH_EDITOR
		NewNickedActor->SetFolderPath(AMyFooGameGameMode::kFolderPath);
#endif // WITH_EDITOR
	}
}

void ASomeActor::test_SpawnMyTestSimpleActor()
{
	UWorld* World = GetWorld();
	if (!World)
		return;
	
	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = GetActorRotation();
	
	auto* NewTestMyActor = World->SpawnActor<AMyTestSimpleActor>(MyTestSimpleActorClass, SpawnLocation, SpawnRotation);
	if (NewTestMyActor)
	{
		NewTestMyActor->DemoStringFormat();
//		NewTestMyActor->DemoEnum(); // will link error cuz not exposed the Api
			
#if WITH_EDITOR
		NewTestMyActor->SetFolderPath(AMyFooGameGameMode::kFolderPath);
#endif // WITH_EDITOR
	}
}
