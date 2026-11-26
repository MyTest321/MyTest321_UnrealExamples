// Fill out your copyright notice in the Description page of Project Settings.


#include "NicknamedActor.h"

// Sets default values
ANicknamedActor::ANicknamedActor()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ANicknamedActor::BeginPlay()
{
	Super::BeginPlay();
}

void ANicknamedActor::SayNickname()
{
	UE_LOG(LogTemp, Warning, TEXT("NicknamedActor::SayNickname"));
}

