#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyExample006_Character.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class UNREAL_CPP_API AMyExample006_Character : public ACharacter {
	GENERATED_BODY()
public:
	AMyExample006_Character();

	UPROPERTY(EditAnywhere, Transient)
	float BlockMoveCurveValue = 0;

	UPROPERTY(VisibleAnywhere, Transient)
	bool MyCrouch = false;

	UPROPERTY(EditAnywhere)
	TWeakObjectPtr<AActor> Target;

	void MyEquip();
	void MyFire();
	void MyJump();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;
};
