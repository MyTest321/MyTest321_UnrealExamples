#pragma once

struct MyEnum {
	MyEnum() = delete;
public:
	template<class T> using IntType = typename std::underlying_type<T>::type;

	template<class T> inline static
	typename IntType<T> ToInt(const T& V) {
		static_assert(std::is_enum_v<T>);
		return static_cast<typename IntType<T>::Type>(V);
	}

	template<class T> inline static
	int NumEnums() {
		static_assert(std::is_enum_v<T>);
		return StaticEnum<T>()->NumEnums();
	}

	template<class T, class Handler> inline static
	void Foreach(Handler foreachHandler) {
		static_assert(std::is_enum_v<T>);
		auto* E = StaticEnum<T>();
		auto n  = E->NumEnums();
		for (auto i = 0; i < n; ++i) {
			auto eValue = E->GetValueByIndex(i);
			FName eName = E->GetNameByIndex(i);
			foreachHandler(i, eName, static_cast<T>(eValue));
		}
	}

	template<class T> inline static
	FName ToFName(const T& v) {
		static_assert(std::is_enum_v<T>);
		return StaticEnum<T>()->GetNameByValue(ToInt(v));
	}
	
	template<class T> inline static
	FString ToString(const T& v) {
		static_assert(std::is_enum_v<T>);
		auto* E = StaticEnum<T>();
		auto Name = E->GetNameByValue(static_cast<int64>(v));
		auto TypeNameLen = E->GetFName().GetStringLength();
		return Name.ToString().RightChop(TypeNameLen + 2); // remove 'EnumType::'
	}
};

