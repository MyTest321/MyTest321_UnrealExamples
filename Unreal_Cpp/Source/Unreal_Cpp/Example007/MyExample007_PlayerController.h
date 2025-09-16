#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyExample007_PlayerController.generated.h"

class AMyExample007_Character;
class APawn;

UCLASS(ClassGroup = MyExample007)
class UNREAL_CPP_API AMyExample007_PlayerController : public APlayerController {
	GENERATED_BODY()
public:
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly)
	float BaseTurnRightRate;

	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly)
	float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, Transient)
	AMyExample007_Character* MyCharacter = nullptr;

	UPROPERTY(VisibleAnywhere, Transient)
	FVector InputDirection;

	AMyExample007_PlayerController();

protected:
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupInputComponent() override;

	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

private:
	void OnInputAxis_MoveForward(float Value);
	void OnInputAxis_MoveRight(float Value);

	void OnInputAxis_TurnRightRate(float Value);
	void OnInputAxis_TurnRight(float Value);
	void OnInputAxis_LookUpRate(float Value);
	void OnInputAxis_LookUp(float Value);

	void Crouch_IE_Pressed();
	void Equip_IE_Pressed();
	void Fire_IE_Pressed();
	void Jump_IE_Pressed();
};
