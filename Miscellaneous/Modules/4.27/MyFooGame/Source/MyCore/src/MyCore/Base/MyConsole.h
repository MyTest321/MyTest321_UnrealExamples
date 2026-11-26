#pragma once

struct MYCORE_API MyConsole
{
	MyConsole() = delete;

	static void SetVar(const TCHAR* Name, int InValue);
	static bool GetVar(const TCHAR* Name, int& OutValue);

	static void SetVar(const TCHAR* Name, float InValue);
	static bool GetVar(const TCHAR* Name, float& OutValue);

	static void SetVar(const TCHAR* Name, bool InValue);
	static bool GetVar(const TCHAR* Name, bool& OutValue);

	static void SetVar(const TCHAR* Name, const TCHAR* InValue);
	static bool GetVar(const TCHAR* Name, FString& OutValue);

#if WITH_EDITOR
	static void EditorCmd(const TCHAR* Cmd);
	static void ViewportCmd(const TCHAR* Cmd);
#endif // WITH_EDITOR

private:
	template<class T>
	static inline void SetVarImpl(const TCHAR* Name, T InValue);
};
