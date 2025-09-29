#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "MyExample001_Character.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UInputComponent;
struct FInputActionValue;

UENUM()
enum class EMyExample001_CameraPos
{
	SW = 0,
	SE = 1,
	NE = 2,
	NW = 3,
	_End,
};

UCLASS(config=Game)
class AMyExample001_Character : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(Category = "MyExample001", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true")) USpringArmComponent* CameraBoom;
	UPROPERTY(Category = "MyExample001", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true")) UCameraComponent* FollowCamera;

	UPROPERTY(Category = "MyExample001", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true")) TObjectPtr<UInputMappingContext> DefaultMappingContext;
	UPROPERTY(Category = "MyExample001", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true")) TObjectPtr<UInputAction> IA_Jump;
	UPROPERTY(Category = "MyExample001", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true")) TObjectPtr<UInputAction> IA_Move;
	UPROPERTY(Category = "MyExample001", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true")) TObjectPtr<UInputAction> IA_CameraPos;

public:
	using ECameraPos = EMyExample001_CameraPos;

	AMyExample001_Character();

	FORCEINLINE USpringArmComponent* GetCameraBoom()	const { return CameraBoom; }
	FORCEINLINE UCameraComponent*	 GetFollowCamera()	const { return FollowCamera; }

	void SetCameraPos(ECameraPos NewCameraPos);

	UPROPERTY(Category = "MyExample001", EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float CameraOffset = 0;

	UPROPERTY(Category = "MyExample001", VisibleAnywhere, Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EMyExample001_CameraPos CameraPos = EMyExample001_CameraPos::_End;

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void NotifyControllerChanged() override;

	void IA_Move_Triggered		(const FInputActionValue& Value);

	void IA_Jump_Started		(const FInputActionValue& Value);
	void IA_Jump_Completed		(const FInputActionValue& Value);

	void IA_CameraPos_Started	(const FInputActionValue& Value);
};

