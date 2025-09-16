#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyExample007_AnimInstance.generated.h"

class AMyExample007_Character;
class UAnimSequence;

UCLASS(ClassGroup = MyExample007)
class UNREAL_CPP_API UMyExample007_AnimInstance : public UAnimInstance {
	GENERATED_BODY()
public:	
	UMyExample007_AnimInstance();

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

	UPROPERTY(EditAnywhere, Transient, BlueprintReadOnly)
	float UpperSlotWeight = 0;

	UPROPERTY(VisibleAnywhere, Transient)
	AMyExample007_Character* MyCharacter = nullptr;

protected:
	virtual void NativeInitializeAnimation() override;
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;
private:
	void _UpdateMove();
	void _UpdateAim();
	void _UpdateSlotWeight();

	float GetMontageSlotWeight(FName slot);

	void _DumpSlotNames();
};
