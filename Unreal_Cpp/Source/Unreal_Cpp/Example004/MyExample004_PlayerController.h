#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyExample004_PlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

class AMyExample004_Pawn;
struct FInputActionValue;

UCLASS()
class UNREAL_CPP_API AMyExample004_PlayerController : public APlayerController {
	GENERATED_BODY()
public:
	AMyExample004_PlayerController();

	AMyExample004_Pawn* GetMyPwan() const;

	void UpdateCameraTarget();

	UPROPERTY(VisibleAnywhere, Transient)
	FVector InputDirection;

	UPROPERTY(VisibleAnywhere, Transient)
	int CurrentCameraIndex = 0;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupInputComponent() override;

private:
	void OnInputAxis_MoveForward(float Value);
	void OnInputAxis_MoveRight	(float Value);

	void OnInputAction_Jump_Pressed();
	void OnInputAction_Jump_Released();
	void OnInputAction_Jump_Axis();
	void OnInputAction_Jump_Repeat();
	void OnInputAction_Jump_DoubleClick();

	void OnInputAction_MyChangeCamera();
};
