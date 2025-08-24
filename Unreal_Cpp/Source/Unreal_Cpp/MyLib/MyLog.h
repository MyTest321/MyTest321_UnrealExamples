#pragma once

#include "MyFmt.h"
#include "Logging/LogMacros.h"

#define MY_ASSERT(X) check(X)

enum class EMyLogLevel {
	None,
	Info,
	Warning,
	Error,
};

#define MY_LOG(...)				MY_LOG_INFO(__VA_ARGS__)
#define MY_LOG_INFO(...)		do { MyLogger::Log(EMyLogLevel::Info,			MyFormat(__VA_ARGS__)); } while(false)
#define MY_LOG_WARNING(...)		do { MyLogger::Log(EMyLogLevel::Warning,		MyFormat(__VA_ARGS__)); } while(false)
#define MY_LOG_ERROR(...)		do { MyLogger::Log(EMyLogLevel::Error,			MyFormat(__VA_ARGS__)); } while(false)
#define MY_LOG_ON_SCREEN(...)	do { MyLogger::LogOnScreen(__FILE__, __LINE__,	MyFormat(__VA_ARGS__)); } while(false)

struct MyLogger
{
	static void Log(EMyLogLevel Lv, const FString& Msg);
	static void LogOnScreen(const char* Filename, int Line, const FString& Msg);
};

