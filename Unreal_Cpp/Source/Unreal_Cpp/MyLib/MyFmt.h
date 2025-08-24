#pragma once

#pragma push_macro("check")
#pragma push_macro("verify")
#undef check
#undef verify

	#define FMT_HEADER_ONLY 1
	#define FMT_EXCEPTIONS 0

#if defined(UNICODE) || defined(_UNICODE)
	#define FMT_USE_WCHAR 1
	#include "../../Externals/fmt/include/fmt/xchar.h"
	using MyFmt_Context = fmt::wformat_context;
#else
	#define FMT_USE_WCHAR 0
	using MyFmt_Context = fmt::format_context;
#endif

	#include "../../Externals/fmt/include/fmt/core.h"

#pragma pop_macro("check")
#pragma pop_macro("verify")

#include "MyEnum.h"

#include <UObject/ReflectedTypeAccessors.h>

class MyFmt_FStringBackInserter {
	using This = MyFmt_FStringBackInserter;
public:
	MyFmt_FStringBackInserter() = default;
	explicit MyFmt_FStringBackInserter(FString& out) noexcept : _out(&out) {}

	This& operator=(const char   &  ch)	{ _out->AppendChar(ch); return *this; }
	This& operator=(const wchar_t&  ch)	{ _out->AppendChar(ch); return *this; }

	This& operator=(      char	  && ch) { _out->AppendChar(std::move(ch)); return *this; }
	This& operator=(      wchar_t && ch) { _out->AppendChar(std::move(ch)); return *this; }

	template <size_t N> 
	This& operator=(char (&chs)[N]) { if (N) { _out->AppendChars(chs, N - 1); } return *this; }

	template <size_t N> 
	This& operator=(wchar_t (&chs)[N]) { if (N) { _out->AppendChars(chs, N - 1); } return *this; }

	This& operator* ()		noexcept { return *this; }
	This& operator++()		noexcept { return *this; }
	This  operator++(int)	noexcept { return *this; }

private:
	FString* _out = nullptr;
};

template <class... ARGS> inline
void MyAppendFormat(FString & outStr, fmt::wformat_string<ARGS...> Format, const ARGS&... Args) {
	FMT_TRY {
		fmt::format_to(MyFmt_FStringBackInserter(outStr), Format, Args...);
	}
	FMT_CATCH(...) {
		UE_LOG(LogTemp, Error, TEXT("Exception in MyFormat"));
	}
}

template <class... ARGS> inline
void MyAppendFormat(FString& outStr, fmt::format_string<ARGS...> Format, const ARGS&... Args) {
	FMT_TRY {
		fmt::format_to(MyFmt_FStringBackInserter(outStr), Format, Args...);
	}
	FMT_CATCH(...) {
		UE_LOG(LogTemp, Error, TEXT("Exception in MyFormat"));
	}
}

template<class... ARGS> inline
FString MyFormat(const TCHAR* Format, const ARGS& ... Args) {
	static_assert(sizeof...(Args) > 0);
	FString tmp;
	MyAppendFormat(tmp, Format, Args...);
	return tmp;
}

template<class... ARGS> inline
FText MyFormatText(const TCHAR* Format, const ARGS& ... Args) {
	static_assert(sizeof...(Args) > 0);
	FString tmp = MyFormat(Format, Args...);
	return FText::FromString(tmp);
}

template<class... ARGS> inline
FName MyFormatName(const TCHAR* Format, const ARGS& ... Args) {
	static_assert(sizeof...(Args) > 0);
	FString tmp = MyFormat(Format, Args...);
	return FName(tmp);
}

//------
template <>
struct fmt::formatter<FStringView, TCHAR> {
	auto parse(fmt::basic_format_parse_context<TCHAR>& ctx) { return ctx.begin(); }
	auto format(const FStringView& v, MyFmt_Context& ctx) const {
		auto it = *ctx.out();
		for (const auto& c : v) {
			it = c;
			it++;
		}
		return ctx.out();
	}
};

using MyFormatterBase = typename fmt::formatter<FStringView, TCHAR>;

template <>
struct fmt::formatter<FString, TCHAR> : public MyFormatterBase {
	auto format(const FString& v, MyFmt_Context& ctx) const {
		return MyFormatterBase::format(v, ctx);
	}
};

template <>
struct fmt::formatter<FName, TCHAR> : public fmt::formatter<FString, TCHAR> {
	using MyBase = fmt::formatter<FString, TCHAR>;
	auto format(const FName& v, MyFmt_Context& ctx) const {
		return MyBase::format(v.ToString(), ctx);
	}
};

template<>
struct fmt::formatter<FSmartName, TCHAR> : fmt::formatter<FString, TCHAR> {
	using MyBase = fmt::formatter<FString, TCHAR>;
	auto format(const FSmartName& v, MyFmt_Context& ctx) const {
		return MyBase::format(v.DisplayName.ToString(), ctx);
	}
};

template<>
struct fmt::formatter<FText, TCHAR> : fmt::formatter<FString, TCHAR> {
	using MyBase = fmt::formatter<FString, TCHAR>;
	auto format(const FText& v, MyFmt_Context& ctx) const {
		return MyBase::format(v.ToString(), ctx);
	}
};

// enum class
template <class T, class CH>
struct fmt::formatter<T, CH, std::enable_if_t<std::is_enum_v<T>>> : public MyFormatterBase {
	auto format(const T& v, MyFmt_Context& ctx) const {
		return MyFormatterBase::format(MyEnum::ToString(v), ctx);
	}
};

template <class E>
struct fmt::formatter<UE::Math::TVector2<E>, TCHAR> : public MyFormatterBase {
	auto format(const UE::Math::TVector2<E>& v, MyFmt_Context& ctx) const {
		return fmt::format_to(ctx.out(), TEXT("[X={}, Y={}]"), v.X, v.Y);
	}
};

template <class E>
struct fmt::formatter<UE::Math::TVector<E>, TCHAR> : public MyFormatterBase {
	auto format(const UE::Math::TVector<E>& v, MyFmt_Context& ctx) const {
		return fmt::format_to(ctx.out(), TEXT("[X={}, Y={}, Z={}]"), v.X, v.Y, v.Z);
	}
};

template <class E>
struct fmt::formatter<UE::Math::TVector4<E>, TCHAR> : public MyFormatterBase {
	auto format(const UE::Math::TVector4<E>& v, MyFmt_Context& ctx) const {
		return fmt::format_to(ctx.out(), TEXT("[X={}, Y={}, Z={}, W={}]"), v.X, v.Y, v.Z, v.W);
	}
};

template <class E>
struct fmt::formatter<UE::Math::TRotator<E>, TCHAR> : public MyFormatterBase {
	auto format(const UE::Math::TRotator<E>& v, MyFmt_Context& ctx) const {
		return fmt::format_to(ctx.out(), TEXT("Rot[Pitch={}, Yaw={}, Roll={}]"), v.Pitch, v.Yaw, v.Roll);
	}
};

template<>
struct fmt::formatter<FVector2D, TCHAR> : public MyFormatterBase {
	auto format(const FVector2D& v, MyFmt_Context& ctx) const {
		return fmt::format_to(ctx.out(), TEXT("[X={}, Y={}]"), v.X, v.Y);
	}
};

template<>
struct fmt::formatter<FVector, TCHAR> : public MyFormatterBase {
	auto format(const FVector& v, MyFmt_Context& ctx) const {
		return fmt::format_to(ctx.out(), TEXT("[X={}, Y={}, Z={}]"), v.X, v.Y, v.Z);
	}
};

template <>
struct fmt::formatter<FVector_NetQuantize, TCHAR> : public fmt::formatter<FVector, TCHAR> {
	auto format(const FVector_NetQuantize& v, MyFmt_Context& ctx) const {
		return fmt::formatter<FVector, TCHAR>::format(v, ctx);
	}
};

template<>
struct fmt::formatter<AActor, TCHAR> : public MyFormatterBase {
	auto format(const AActor& v, MyFmt_Context& ctx) const {
		static const TCHAR* ksz = TEXT("Nullptr");
		return fmt::format_to(ctx.out(), TEXT("Actor: {}"),
			IsValid(&v) ? v.GetFName() : ksz
		);
	}
};