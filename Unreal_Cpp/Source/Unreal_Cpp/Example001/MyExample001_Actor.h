#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyExample001_Actor.generated.h"

USTRUCT()
struct FMyExample001_MyStruct {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) float x;
	UPROPERTY(EditAnywhere) float y;
};

USTRUCT(NoExport)
struct FMyExample001_MyStruct2 {
	UPROPERTY(EditAnywhere) float x;
	UPROPERTY(EditAnywhere) float y;
};

UCLASS()
class UMyExample001_MyObject : public UObject {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) float x;
	UPROPERTY(EditAnywhere) float y;
};

UENUM()
enum EMyExample001_MyEnum
{
	EMyExample001_A,
	EMyExample001_B,
	EMyExample001_C,
};

UENUM()
enum class EMyExample001_MyEnumClass
{
	A,
	B,
//	C,
	C UMETA(DisplayName = "My Display Name: C"),
};
ENUM_CLASS_FLAGS(EMyExample001_MyEnumClass)

UCLASS()
class UNREAL_CPP_API AMyExample001_Actor : public AActor {
	GENERATED_BODY()
public:	
	AMyExample001_Actor();

protected:
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere)
	int Test_Edit = 0;

	UPROPERTY(VisibleAnywhere)
	int Test_Visible = 0;

	UPROPERTY(EditAnywhere, Category = "My Category")
	int Test_Category = 0;

	UPROPERTY(EditAnywhere, Transient)
	int Test_Transient = 0;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "My Display Name"))
	int Test_DisplayName = 0;

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", ClampMax = "100"))
	int Test_Clamp = 0;

	UPROPERTY(EditAnywhere)
	bool Test_Condition_Bool = false;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "Test_Condition_Bool"))
	int Test_Condition_Int = 0;

	UPROPERTY(EditAnywhere)
	FString Test_FString;

	UPROPERTY(EditAnywhere)
	FName Test_FName;

	UPROPERTY(EditAnywhere)
	FText Test_FText;

	UPROPERTY(EditAnywhere)
	FMyExample001_MyStruct Test_Struct;

	UPROPERTY(EditAnywhere)
	FMyExample001_MyStruct Test_Struct2;

	UPROPERTY(EditAnywhere)
	UMyExample001_MyObject* Test_Objcet = nullptr;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EMyExample001_MyEnum> Test_Enum;
	
	UPROPERTY(EditAnywhere)
	EMyExample001_MyEnumClass Test_EnumClass;

	UFUNCTION(BlueprintCallable)
	void BPCallCpp(int testInt, float testFloat);

	UFUNCTION(BlueprintImplementableEvent)
	void CppCallBPEvent(int testInt, float testFloat);

	void DemoStringFormat();
	void DemoEnum();
};
