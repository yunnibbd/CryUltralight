#pragma once
#include <functional>
#include <JavaScriptCore/JavaScript.h>
#include <CryString/CryString.h>
#include <iostream>

namespace CryUltralight
{

#pragma pack(push, 1)

enum class JSArgType : int32_t
{
	Int = 0,
	Double,
	Bool,
	String
};

struct JSArgPlain
{
	JSArgType type;
	union
	{
		int32_t i;
		double d;
		bool b;
		intptr_t ptr;
	};
	const char* s;
};

#pragma pack(pop)

template<typename T>
JSArgPlain MakePlain(T&&) = delete;

inline JSArgPlain MakePlain(int v)
{
	JSArgPlain arg{};
	arg.type = JSArgType::Int;
	arg.i = v;
	arg.s = nullptr;
	return arg;
}

inline JSArgPlain MakePlain(double v)
{
	JSArgPlain arg{};
	arg.type = JSArgType::Double;
	arg.d = v;
	arg.s = nullptr;
	return arg;
}

inline JSArgPlain MakePlain(bool v)
{
	JSArgPlain arg{};
	arg.type = JSArgType::Bool;
	arg.b = v ? 1 : 0;
	arg.s = nullptr;
	return arg;
}

inline JSArgPlain MakePlain(const char* v)
{
	JSArgPlain arg{};
	arg.type = JSArgType::String;
	arg.ptr = 0;
	arg.s = v;
	return arg;
}

inline JSArgPlain MakePlain(const std::string& v)
{
	JSArgPlain arg{};
	arg.type = JSArgType::String;
	arg.ptr = 0;
	arg.s = v.c_str();
	return arg;
}

class CUltralightView;

class ICUltralightJavaScript
{
public:
	virtual void Initial(CUltralightView* view) = 0;
	virtual void SetReadyCallBack(std::function<void()> cb) = 0;
	virtual string EvaluateScript(const char* script) = 0;

	template<typename Ret = void, typename... Args>
	static Ret Call(ICUltralightJavaScript* js, const char* name, Args&&... args)
	{
		JSArgPlain packed[] = { MakePlain(std::forward<Args>(args))... };
		size_t count = sizeof...(Args);

		if constexpr (std::is_same_v<Ret, void>)
			js->CallVoid(name, packed, count);
		else if constexpr (std::is_same_v<Ret, double>)
			return js->CallNumber(name, packed, count);
		else if constexpr (std::is_same_v<Ret, bool>)
			return js->CallBool(name, packed, count);
		else if constexpr (std::is_same_v<Ret, std::string>)
		{
			const char* ret = js->CallString(name, packed, count);
			return std::string(ret ? ret : "");
		}
		else
			static_assert(sizeof(Ret) == 0, "Unsupported return type in ICUltralightJavaScript::Call");
	}
	
protected:
	virtual void CallVoid(const char* name, const JSArgPlain* args, size_t count) = 0;
	virtual double CallNumber(const char* name, const JSArgPlain* args, size_t count) = 0;
	virtual bool CallBool(const char* name, const JSArgPlain* args, size_t count) = 0;
	virtual const char* CallString(const char* name, const JSArgPlain* args, size_t count) = 0;

protected:
	CUltralightView* m_pUltralightView = nullptr;
};

}