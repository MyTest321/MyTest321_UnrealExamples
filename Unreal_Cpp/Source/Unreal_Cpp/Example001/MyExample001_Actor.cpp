#include "MyExample001_Actor.h"

AMyExample001_Actor::AMyExample001_Actor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AMyExample001_Actor::BeginPlay()
{
	Super::BeginPlay();
	
	DemoStringFormat();
	DemoEnum();
}

void AMyExample001_Actor::DemoStringFormat() {

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
		FString str = MyFormat(TEXT("MyFormat {} {}"), 123, TEXT("string"));
		UE_LOG(LogTemp, Warning, TEXT("%s"), *str);
	}

	{
		FName hello1(TEXT("Hello World"));
		MY_LOG_ERROR(TEXT("{}"), hello1);

		FText hello2(FText::FromString(TEXT("こんにちは世界")));
		MY_LOG_WARNING(TEXT("{}"), hello2);

		MY_LOG(TEXT("{}\n{}\nbool: {}\nint: {}\nfloat: {}\ndouble: {}\nliteral string: {}\nVec3f: {}\n"),
			hello1, hello2,
			true,
			123456,
			1.23f,
			1.23456789,
			TEXT("string"),
			FVector3f(1.f, 2.f, 3.f)
		);
	}
}

void AMyExample001_Actor::DemoEnum() {
	UEnum* EnumInfo = StaticEnum<EMyExample001_MyEnumClass>();
	MyEnum::Foreach<EMyExample001_MyEnumClass>([](int i, FName eName, const EMyExample001_MyEnumClass& eValue) {
		MY_LOG(TEXT("EnumInfo {} {} {}"), i, eName, eValue);
	});

	{
		auto value = static_cast<EMyExample001_MyEnumClass>(EnumInfo->GetValueByNameString("B"));
		MY_LOG(TEXT("EnumInfo GetValueByNameString {}"), value);
	}

	auto EnumBitwiseOr = EMyExample001_MyEnumClass::A | EMyExample001_MyEnumClass::B;
	MY_LOG(TEXT("EnumInfo EnumBitwiseOr {}"), EnumBitwiseOr);
}

void AMyExample001_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

