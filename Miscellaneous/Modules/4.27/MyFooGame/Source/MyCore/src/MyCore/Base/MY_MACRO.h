#pragma once

#include "Runtime/Launch/Resources/Version.h"

#if ENGINE_MAJOR_VERSION == 5
    #define IS_UE5 1
    #define IS_UE4 0
	
	#if ENGINE_MINOR_VERSION >= 3
		#define IS_UE5_3 1
	#endif
	
#elif ENGINE_MAJOR_VERSION == 4
    #define IS_UE5 0
    #define IS_UE4 1
#else
    #error "Unsupported Unreal Engine version!"
#endif


#define MY_ASSERT(X) check(X)
#define MY_NOT_IMPL(...) do { unimplemented(); _THROW(); } while(false)

#define MY_CONCAT_1(v0) v0
#define MY_CONCAT_2(v0, v1) v0##v1
#define MY_CONCAT_3(v0, v1, v2) v0##v1##v2
#define MY_CONCAT_4(v0, v1, v2, v3) v0##v1##v2##v3

#define MY_LOG(...)				MY_LOG_INFO(__VA_ARGS__)
#define MY_LOG_INFO(...)		do { MyLogger::Log(EMyLogLevel::Info,			MyFormat(__VA_ARGS__)); } while(false)
#define MY_LOG_WARNING(...)		do { MyLogger::Log(EMyLogLevel::Warning,		MyFormat(__VA_ARGS__)); } while(false)
#define MY_LOG_ERROR(...)		do { MyLogger::Log(EMyLogLevel::Error,			MyFormat(__VA_ARGS__)); } while(false)
#define MY_LOG_ON_SCREEN(...)	do { MyLogger::LogOnScreen(__FILE__, __LINE__,	MyFormat(__VA_ARGS__)); } while(false)

