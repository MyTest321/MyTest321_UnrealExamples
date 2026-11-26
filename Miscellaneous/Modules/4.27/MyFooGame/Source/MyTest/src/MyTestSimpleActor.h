// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyTestSimpleActor.generated.h"

USTRUCT()
struct FMyExample001_MyStruct {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) float x;
	UPROPERTY(EditAnywhere) float y;
};

#if 0
USTRUCT(NoExport)
struct FMyExample001_MyStruct2 {
	UPROPERTY(EditAnywhere) float x;
	UPROPERTY(EditAnywhere) float y;
};
#else
USTRUCT()
struct FMyExample001_MyStruct2 {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) float x;
	UPROPERTY(EditAnywhere) float y;
};

#endif

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

UCLASS(Blueprintable, MinimalAPI)
class AMyTestSimpleActor : public AActor
{
	GENERATED_BODY()
public:	
	AMyTestSimpleActor();
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

	UFUNCTION(BlueprintCallable)
	void BPCallCpp(int testInt, float testFloat);

	UFUNCTION(BlueprintImplementableEvent)
	void CppCallBPEvent(int testInt, float testFloat);

	UFUNCTION(BlueprintCallable)
	MYTEST_API void DemoStringFormat();
	
	UFUNCTION(BlueprintCallable)
	void DemoEnum();

};
