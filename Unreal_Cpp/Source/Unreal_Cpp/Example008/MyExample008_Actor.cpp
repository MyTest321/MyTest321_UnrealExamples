#include "MyExample008_Actor.h"

static void MyExample008_Actor_C_Static_Function(const FName& name, int testInt, float testFloat)
{
	MY_LOG_INFO(TEXT("[{}]: C_Static_Function ({}, {})"), name, testInt, testFloat);
}

AMyExample008_Actor::AMyExample008_Actor() {
}

void AMyExample008_Actor::BeginPlay()
{
	Super::BeginPlay();
	MY_LOG_WARNING(TEXT("AMyExample008_Actor BeginPlay"));

	TestEvent.AddStatic(&MyExample008_Actor_C_Static_Function);
	TestEvent.AddStatic(&ThisClass::s_OnStaticMemberFunction);

	TestEvent.AddUObject(this, &ThisClass::OnTestFunction);
//	TestEvent.AddSP();

	TestEvent.AddUFunction(this, TEXT("OnTestUFunction")); //!!<---- AddUFunction may crash, when function not found

	// try AddUFunction
	static FName kFunctionName_OnTestCppCallBlueprintEvent = TEXT("OnTestCppCallBlueprintEvent");
	if (UFunction* Function = FindFunction(kFunctionName_OnTestCppCallBlueprintEvent))
	{
		if (Function->GetOuter() == GetClass()) // or Function == GetClass()->FindFunctionByName(kFunctionName_OnTestCppCallBlueprintEvent)
		{
			TestEvent.AddUFunction(this, kFunctionName_OnTestCppCallBlueprintEvent);
			MY_LOG_INFO(TEXT("Founded Method {}"), kFunctionName_OnTestCppCallBlueprintEvent);
		}
		else
		{
			MY_LOG_ERROR(TEXT("Not Found Method {}"), kFunctionName_OnTestCppCallBlueprintEvent);
		}
	}
	else
	{
		MY_LOG_ERROR(TEXT("Not Found Method {}"), kFunctionName_OnTestCppCallBlueprintEvent);
	}

	TestEvent.AddLambda([](const FName& name, int testInt, int testFloat) {
		MY_LOG_INFO(TEXT("[{}]: OnTestLambda: ({}, {})"), name, testInt, testFloat);
	});

	if (TestDynamicDelegate.IsBound())
	{
		TestDynamicDelegate.Execute(TEXT("TestDynamicDelegate"), 0, 0);
	}
	else
	{
		MY_LOG_INFO(TEXT("Not Bind TestDynamicDelegate"));
	}
	TestDynamicDelegate.BindDynamic(this, &ThisClass::OnTestDynamicDelegate);

	TestDynamicEvent.AddDynamic(this, &ThisClass::OnTestDynamicEvent);
	TestDynamicEvent.AddDynamic(this, &ThisClass::OnTestDynamicEvent); //!!<--- add redundant same function will call twice

// --------
	TestDelegate.ExecuteIfBound(TEXT("TestDelegate"), 0, 1);
	TestEvent.Broadcast(TEXT("TestEvent"), 1, 2);

	TestDynamicDelegate.ExecuteIfBound(TEXT("TestDynamicDelegate ExecuteIfBound"), 3, 4);
	TestDynamicEvent.Broadcast(TEXT("TestDynamicEvent"), 4, 5);

	TestDynamicEvent.RemoveDynamic(this, &ThisClass::OnTestDynamicEvent); //!!<--- only remove one callback
	TestDynamicEvent.Broadcast(TEXT("TestDynamicEvent2"), 5, 6);

	TestDynamicEvent.RemoveDynamic(this, &ThisClass::OnTestDynamicEvent); //!!<--- now callback is empty
	TestDynamicEvent.Broadcast(TEXT("TestDynamicEvent3"), 6, 7);

	OnTestCppCallBlueprintEvent(TEXT("OnTestCppCallBlueprintEvent"), 7, 8);
}

void AMyExample008_Actor::s_OnStaticMemberFunction(const FName& name, int testInt, float testFloat)
{
	MY_LOG_INFO(TEXT("[{}]: OnStaticMemberFunction ({}, {})"), name, testInt, testFloat);
}

void AMyExample008_Actor::OnTestFunction(const FName& name, int testInt, float testFloat)
{
	MY_LOG_INFO(TEXT("[{}]: OnTestFunction ({}, {})"), name, testInt, testFloat);
}

void AMyExample008_Actor::OnTestUFunction(const FName& name, int testInt, float testFloat)
{
	MY_LOG_INFO(TEXT("[{}]: OnTestUFunction ({}, {})"), name, testInt, testFloat);
}

void AMyExample008_Actor::OnTestDynamicDelegate(const FName& name, int testInt, float testFloat)
{
	MY_LOG_INFO(TEXT("[{}]: OnTestDynamicDelegate ({}, {})"), name, testInt, testFloat);
}

void AMyExample008_Actor::OnTestDynamicEvent(const FName& name, int testInt, float testFloat)
{
	MY_LOG_INFO(TEXT("[{}]: OnTestDynamicEvent ({}, {})"), name, testInt, testFloat);
}

void AMyExample008_Actor::OnTestBPCallCpp(const FName& name, int testInt, float testFloat)
{
	MY_LOG_WARNING(TEXT("[{}]: OnTestBPCallCpp ({}, {})"), name, testInt, testFloat);
}

void AMyExample008_Actor::BeginDestroy()
{
	MY_LOG_WARNING(TEXT("AMyExample008_Actor BeginDestroy"));

	TestDelegate.Unbind();
	TestEvent.Clear();
	TestDynamicDelegate.Unbind();
	TestDynamicEvent.Clear();

	Super::BeginDestroy();
}