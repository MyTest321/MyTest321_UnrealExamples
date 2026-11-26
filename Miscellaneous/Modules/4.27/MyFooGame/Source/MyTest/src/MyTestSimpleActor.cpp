// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTestSimpleActor.h"

// Sets default values
AMyTestSimpleActor::AMyTestSimpleActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AMyTestSimpleActor::BeginPlay()
{
	Super::BeginPlay();
	
	DemoStringFormat();
	DemoEnum();
}

void AMyTestSimpleActor::BPCallCpp(int testInt, float testFloat)
{
	MY_LOG_WARNING("BPCallCpp ({}, {})", testInt, testFloat);
}

void AMyTestSimpleActor::DemoStringFormat()
{
	const char*	   sz = "Hello";
	const wchar_t* wcs = L"Hello";
	const TCHAR*   tcs = TEXT("Hello");

	{
		FString str = FString::Printf(TEXT("FString Printf %d %d %f %s"), 1, 2, 1.23f, TEXT("Hi!"));
		UE_LOG(LogTemp, Warning, TEXT("%s"), *str);
	}

	{
		FString str = FString::Printf(TEXT("FString Printf is unsafe %s"), "Hi!");
		UE_LOG(LogTemp, Warning, TEXT("%s"), *str);
	}

	{
		FStringFormatOrderedArguments fmtArgs;
		fmtArgs.Add(123);
		fmtArgs.Add(2);
		fmtArgs.Add(1.23f);
		fmtArgs.Add(TEXT("Hi!"));
		FString str = FString::Format(TEXT("FString Format Ordered {0} {1} {2} {3}"), fmtArgs);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *str);
	}

	{
		FStringFormatNamedArguments Args;
		Args.Add("A", 123);
		Args.Add("B", 2);
		Args.Add("C", 1.23f);
		Args.Add("D", TEXT("Hi!"));
		FString str = FString::Format(TEXT("FString Format Named {A} {B} {C} {D}"), Args);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *str);
	}

	{
		FString str = MyFormat("MyFmt {} {}", 123, "string");
		UE_LOG(LogTemp, Warning, TEXT("%s"), *str);
	}

	{
		FName hello1(TEXT("Hello World"));
		MY_LOG_ERROR("{}", hello1);

		FText hello2(FText::FromString(TEXT("こんにちは世界")));
		MY_LOG_WARNING("{}", hello2);

		MY_LOG("{}\n{}\nbool: {}\nint: {}\nfloat: {}\ndouble: {}\nliteral string: {}\nVec3f: {}\n",
			hello1, hello2,
			true,
			123456,
			1.23f,
			1.23456789,
			"string",
			FVector(1.f, 2.f, 3.f)
		);
	}
}

void AMyTestSimpleActor::DemoEnum() {
	UEnum* EnumInfo = StaticEnum<EMyExample001_MyEnumClass>();
	MyEnum::Foreach<EMyExample001_MyEnumClass>([](int i, FName eName, const EMyExample001_MyEnumClass& eValue) {
		MY_LOG("EnumInfo {} {} {}", i, eName, eValue);
	});

	{
		auto value = static_cast<EMyExample001_MyEnumClass>(EnumInfo->GetValueByNameString("B"));
		MY_LOG("EnumInfo GetValueByNameString {}", value);
	}

	auto EnumBitwiseOr = EMyExample001_MyEnumClass::A | EMyExample001_MyEnumClass::B;
	MY_LOG("EnumInfo EnumBitwiseOr {}", EnumBitwiseOr);
}