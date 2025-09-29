#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "MyExample002_CameraActor.generated.h"

class UBoxComponent;
class AUnreal_CameraCharacter;

UCLASS()
class AMyExample002_CameraActor : public ACameraActor {
	GENERATED_BODY()
public:
	UPROPERTY(Category = "MyExample002", VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> BoxComp;

	AMyExample002_CameraActor();

	UPROPERTY(Category = "MyExample002", EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0.0f))
	float CameraBlendTime = 1.f;

	UPROPERTY(Category = "MyExample002", EditAnywhere, BlueprintReadWrite)
	TArray< TObjectPtr<UBoxComponent> > BoxComps;

protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	void EnsureComponentAttachments();
	bool IsMyCharacterOverlappingBox(AUnreal_CameraCharacter* Character);

    UFUNCTION()
	void OnComponentBeginOverlap_Box(UPrimitiveComponent* OverlappedComponent, 
									 AActor* OtherActor, 
									 UPrimitiveComponent* OtherComp, 
									 int32 OtherBodyIndex, 
									 bool bFromSweep, 
									 const FHitResult& SweepResult);

    UFUNCTION()
	void OnComponentEndOverlap_Box(UPrimitiveComponent* OverlappedComponent, 
								   AActor* OtherActor, 
								   UPrimitiveComponent* OtherComp, 
								   int32 OtherBodyIndex);
};
