#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyExample007_Character.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UAnimMontage;

class UMyExample007_AnimInstance;
class AMyExample007_Bullet;

UCLASS(ClassGroup = MyExample007)
class UNREAL_CPP_API AMyExample007_Character : public ACharacter {
	GENERATED_BODY()
public:
	AMyExample007_Character();

	UPROPERTY(VisibleAnywhere, Transient)
	bool MyCrouch = false;

	UPROPERTY(EditAnywhere) TWeakObjectPtr<AActor> Target;

	UPROPERTY(EditAnywhere) TObjectPtr<UAnimMontage> Montage_Equip;
	UPROPERTY(EditAnywhere) TObjectPtr<UAnimMontage> Montage_Fire_Upper;

	UPROPERTY(Category = "MyExample007", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AMyExample007_Bullet> BulletToSpawnClass;

	UPROPERTY(EditAnywhere, Transient)
	float BlockMoveCurveValue = 0.f;

	UMyExample007_AnimInstance* MyAnimInstance();
	const USkeletalMeshSocket*	MyFindSocket(FName name);

	void MyEquip();
	void MyFire();
	void MyJump();

	void CalcAimOffset(float& AimUp, float& AimRight);

	void AnimNotify_Fire();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

	TWeakObjectPtr<USkeletalMeshSocket const> SpawnBulletSocket;
	TWeakObjectPtr<USkeletalMeshSocket const> AimStartSocket;
};
