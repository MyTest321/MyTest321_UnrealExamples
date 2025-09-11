#pragma once

#include "CoreMinimal.h"
#include "MyExample008_Actor.generated.h"


DECLARE_DELEGATE_ThreeParams		  (FMyExample008_TestDelegate, const FName&, int, float);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FMyExample008_TestEvent,    const FName&, int, float);

DECLARE_DYNAMIC_DELEGATE_ThreeParams		  (FMyExample008_TestDynamicDelegate, const FName&, name, int, testInt, float, testFloat);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FMyExample008_TestDynamicEvent,	  const FName&, name, int, testInt, float, testFloat);

UCLASS()
class UNREAL_CPP_API AMyExample008_Actor : public AActor {
	GENERATED_BODY()
public:

	// https://docs.unrealengine.com/4.27/en-US/ProgrammingAndScripting/ProgrammingWithCPP/UnrealArchitecture/Delegates/Dynamic/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FMyExample008_TestDynamicDelegate TestDynamicDelegate;

	UPROPERTY(EditAnywhere, BlueprintAssignable)
	FMyExample008_TestDynamicEvent TestDynamicEvent;

	AMyExample008_Actor();

	static void s_OnStaticMemberFunction(const FName& name, int testInt, float testFloat);

	void OnTestFunction(const FName& name, int testInt, float testFloat);

	UFUNCTION()
	void OnTestUFunction(const FName& name, int testInt, float testFloat);

	UFUNCTION(BlueprintCallable)
	void OnTestBPCallCpp(const FName& name, int testInt, float testFloat);

	UFUNCTION(BlueprintImplementableEvent, meta = (DeprecatedFunction, DeprecationMessage = "Use OnTestCppCallBlueprintEvent Instead"))
	void OnTestCppCallBPEvent(const FName& name, int testInt, float testFloat) UE_DEPRECATED(5.0, "OnTestCppCallBlueprintEvent");

	UFUNCTION(BlueprintImplementableEvent)
	void OnTestCppCallBlueprintEvent(const FName& name, int testInt, float testFloat);

	UFUNCTION()
	void OnTestDynamicDelegate(const FName& name, int testInt, float testFloat);
	UFUNCTION()
	void OnTestDynamicEvent(const FName& name, int testInt, float testFloat);

protected:
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

private:
	FMyExample008_TestDelegate TestDelegate;
	FMyExample008_TestEvent	   TestEvent;
};
