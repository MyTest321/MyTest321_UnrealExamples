// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyExample003_BlendTriggerVolume.generated.h"

class UBoxComponent;
class ACameraActor;
class AUnreal_CameraCharacter;

UCLASS()
class UNREAL_CAMERA_API AMyExample003_BlendTriggerVolume : public AActor
{
	GENERATED_BODY()
public:	
	AMyExample003_BlendTriggerVolume();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(Category = "MyExample003", EditAnywhere, BlueprintReadWrite) TObjectPtr<UBoxComponent> OverlapVolume;
	UPROPERTY(Category = "MyExample003", EditAnywhere, BlueprintReadWrite) TSubclassOf<ACameraActor> CameraToFind_CameraActorClass;
	UPROPERTY(Category = "MyExample003", EditAnywhere, BlueprintReadWrite, meta =(ClampMin = 0.0f)) float CameraBlendTime = 1.f;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
};
