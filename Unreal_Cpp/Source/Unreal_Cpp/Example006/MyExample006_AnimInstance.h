#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyExample006_AnimInstance.generated.h"

class AMyExample006_Character;

UCLASS()
class UNREAL_CPP_API UMyExample006_AnimInstance : public UAnimInstance {
	GENERATED_BODY()
public:	
	UMyExample006_AnimInstance();

	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly, meta = (ClampMin = "-1", ClampMax = "1"))
	float MoveForward = 0.f;

	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly, meta = (ClampMin = "-1", ClampMax = "1"))
	float MoveRight = 0.f;

	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly)
	bool MyCrouch = false;

	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly, meta = (ClampMin = "-90", ClampMax = "90"))
	float AimUp = 0;

	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly, meta = (ClampMin = "-90", ClampMax = "90"))
	float AimRight = 0;

	UPROPERTY(VisibleAnywhere, Transient)
	AMyExample006_Character* MyCharacter = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimSequence* TestAnim = nullptr;

protected:
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;
private:
	void _UpdateMove();
	void _UpdateAim();
};
