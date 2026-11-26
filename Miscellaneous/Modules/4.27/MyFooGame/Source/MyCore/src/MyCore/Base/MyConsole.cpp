#include "MyConsole.h"
#include "MyLog.h"

template<class T> inline
void MyConsole::SetVarImpl(const TCHAR* Name, T InValue)
{
	auto* V = IConsoleManager::Get().FindConsoleVariable(Name);
	if (!V)
	{
		/*MY_LOG_ERROR(TEXT("SetConsoleVar() Cannot find console var '{}'"), Name);*/
		UE_LOG(LogTemp, Error, TEXT("Cannot find console var %s"), Name);
		return;
	}
	V->Set(InValue);
}

void MyConsole::SetVar(const TCHAR* Name, int			InValue) { SetVarImpl(Name, InValue); }
void MyConsole::SetVar(const TCHAR* Name, float			InValue) { SetVarImpl(Name, InValue); }
void MyConsole::SetVar(const TCHAR* Name, bool			InValue) { SetVarImpl(Name, InValue); }
void MyConsole::SetVar(const TCHAR* Name, const TCHAR*	InValue) { SetVarImpl(Name, InValue); }

#define MY_GetVal_Impl(T, GET_METHOD) \
bool MyConsole::GetVar(const TCHAR* Name, T& OutValue) \
{ \
	auto* V = IConsoleManager::Get().FindConsoleVariable(Name); \
	if (!V) \
	{ \
		UE_LOG(LogTemp, Error, TEXT("Cannot find console var %s"), Name); \
		/*MY_LOG_ERROR(TEXT("Cannot find console var '{}'"), Name);*/ \
		return false; \
	} \
	OutValue = V->GET_METHOD; \
	return true; \
} \
// --------
	MY_GetVal_Impl(int, GetInt())
	MY_GetVal_Impl(float, GetFloat())
	MY_GetVal_Impl(bool, GetBool())
	MY_GetVal_Impl(FString, GetString())
#undef MY_GetVal_Impl

#if WITH_EDITOR
void MyConsole::EditorCmd(const TCHAR* Cmd)
{
	if (!GEditor)
		return;

	if (auto* World = GEditor->GetEditorWorldContext().World())
	{
		GEditor->Exec(World, Cmd);
	}
}

void MyConsole::ViewportCmd(const TCHAR* Cmd)
{
	if (!GEditor)
		return;

	if (auto* World = GEngine->GetCurrentPlayWorld())
	{
		UKismetSystemLibrary::ExecuteConsoleCommand(World, Cmd);
	}
}
#endif // WITH_EDITOR
