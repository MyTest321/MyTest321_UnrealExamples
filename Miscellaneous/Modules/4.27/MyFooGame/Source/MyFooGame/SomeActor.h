#pragma once

#include "MyFooGame-Common.h"
#include "SomeActor.generated.h"

UCLASS()
class ASomeActor : public AActor {
	GENERATED_BODY()
public:	
	ASomeActor();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* VisualMesh;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ANicknamedActor> NicknamedActorClass;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AMyTestSimpleActor> MyTestSimpleActorClass;
	
protected:
	virtual void BeginPlay() override;
private:
	void test_SpawnNickedActor();
	void test_SpawnMyTestSimpleActor();
};
