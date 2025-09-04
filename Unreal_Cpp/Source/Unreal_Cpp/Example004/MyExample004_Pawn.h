#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyExample004_Pawn.generated.h"

UCLASS()
class UNREAL_CPP_API AMyExample004_Pawn : public APawn {
	GENERATED_BODY()
public:
	AMyExample004_Pawn();

	virtual void BeginPlay() override;
};
