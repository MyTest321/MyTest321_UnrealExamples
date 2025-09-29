// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyExample004_BlendTriggerVolume.generated.h"

class UBoxComponent;
class ACameraActor;
class AUnreal_CameraCharacter;

UCLASS()
class UNREAL_CAMERA_API AMyExample004_BlendTriggerVolume : public AActor
{
	GENERATED_BODY()
public:	
	AMyExample004_BlendTriggerVolume();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(Category = "MyExample004", EditAnywhere, BlueprintReadWrite) TObjectPtr<UBoxComponent> OverlapVolume;
	UPROPERTY(Category = "MyExample004", EditAnywhere, Transient) TWeakObjectPtr<ACameraActor> CameraToFind;
	UPROPERTY(Category = "MyExample004", EditAnywhere, BlueprintReadWrite, meta =(ClampMin = 0.0f)) float CameraBlendTime = 1.f;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
};
