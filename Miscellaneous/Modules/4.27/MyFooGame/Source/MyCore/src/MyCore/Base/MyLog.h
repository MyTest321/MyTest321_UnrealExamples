#pragma once

#include "MyFormat.h"
#include "Logging/LogMacros.h"

enum class EMyLogLevel {
	None,
	Info,
	Warning,
	Error,
};

struct MYCORE_API MyLogger
{
	static void Log(EMyLogLevel Lv, const FString& Msg);
	static void LogOnScreen(const char* Filename, int Line, const FString& Msg);
};

