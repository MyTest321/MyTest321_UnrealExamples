// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NicknamedActor.generated.h"

UCLASS()
class FOOBAR_API ANicknamedActor : public AActor
{
	GENERATED_BODY()
public:	
	ANicknamedActor();

	UPROPERTY(EditAnywhere)
	FName MyName;
	
protected:
	virtual void BeginPlay() override;

public:
	void SayNickname();
};
