#include "StdAfx.h"
#include "UltralightJavaScript.h"
#include "UltralightView.h"
#include <JavaScriptCore/JSRetainPtr.h>
#include <JavaScriptCore/JavaScript.h>

namespace CryUltralight
{

class CUltralightJavaScript::Impl
{
public:
	JSValueRef Convert(JSContextRef ctx, const JSArgPlain& arg)
	{
		switch (arg.type)
		{
		case JSArgType::Int:
			return JSValueMakeNumber(ctx, arg.i);
		case JSArgType::Double:
			return JSValueMakeNumber(ctx, arg.d);
		case JSArgType::Bool:
			return JSValueMakeBoolean(ctx, arg.b != 0);
		case JSArgType::String:
		{
			JSStringRef str = JSStringCreateWithUTF8CString(arg.s ? arg.s : "");
			JSValueRef val = JSValueMakeString(ctx, str);
			JSStringRelease(str);
			return val;
		}
		default:
			return JSValueMakeUndefined(ctx);
		}
	}

	JSValueRef CallInternal(JSContextRef jsCtx,
		const char* name,
		const JSArgPlain* args,
		size_t count)
	{
		if (!jsCtx || !name)
			return nullptr;

		JSObjectRef global = JSContextGetGlobalObject(jsCtx);

		JSStringRef str = JSStringCreateWithUTF8CString(name);
		JSValueRef funcVal = JSObjectGetProperty(jsCtx, global, str, nullptr);
		JSStringRelease(str);

		if (!JSValueIsObject(jsCtx, funcVal))
			return nullptr;

		JSObjectRef func = JSValueToObject(jsCtx, funcVal, nullptr);

		std::vector<JSValueRef> jsArgs;
		jsArgs.reserve(count);

		for (size_t i = 0; i < count; ++i)
			jsArgs.push_back(Convert(jsCtx, args[i]));

		return JSObjectCallAsFunction(
			jsCtx,
			func,
			global,
			count,
			count > 0 ? jsArgs.data() : nullptr,
			nullptr
		);
	}
};

CUltralightJavaScript::CUltralightJavaScript()
	: m_impl(std::make_unique<Impl>())
{
}

void CUltralightJavaScript::Initial(CUltralightView* view)
{
	m_pUltralightView = view;
	view->m_view->set_load_listener(this);
}

void CUltralightJavaScript::SetReadyCallBack(std::function<void()> cb)
{
	m_onDOMReadyCB = cb;
}

string CUltralightJavaScript::EvaluateScript(const char* script)
{
	CRY_ASSERT(m_pUltralightView);
	ultralight::String scriptRet = m_pUltralightView->m_view->EvaluateScript(script);
	return scriptRet.utf8().data();
}

void CUltralightJavaScript::OnDOMReady(ultralight::View* caller, uint64_t frame_id, bool is_main_frame, const ultralight::String& url)
{
	if (!is_main_frame || !m_onDOMReadyCB)
		return;

	m_onDOMReadyCB();
}

void CUltralightJavaScript::CallVoid(const char* name, const JSArgPlain* args, size_t count)
{
	auto scoped_context = m_pUltralightView->m_view->LockJSContext();
	m_impl->CallInternal(*scoped_context, name, args, count);
}

double CUltralightJavaScript::CallNumber(const char* name, const JSArgPlain* args, size_t count)
{
	auto scoped_context = m_pUltralightView->m_view->LockJSContext();
	JSContextRef jsCtx = *scoped_context;
	JSValueRef v = m_impl->CallInternal(jsCtx, name, args, count);
	return JSValueToNumber(jsCtx, v, nullptr);
}

bool CUltralightJavaScript::CallBool(const char* name, const JSArgPlain* args, size_t count)
{
	auto scoped_context = m_pUltralightView->m_view->LockJSContext();
	JSContextRef jsCtx = *scoped_context;
	JSValueRef v = m_impl->CallInternal(jsCtx, name, args, count);
	return JSValueToBoolean(jsCtx, v);
}

const char* CUltralightJavaScript::CallString(const char* name, const JSArgPlain* args, size_t count)
{
	auto scoped_context = m_pUltralightView->m_view->LockJSContext();
	JSContextRef jsCtx = *scoped_context;

	JSValueRef v = m_impl->CallInternal(jsCtx, name, args, count);

	if (!v)
		return "";

	JSStringRef jsStr = JSValueToStringCopy(jsCtx, v, nullptr);

	size_t maxSize = JSStringGetMaximumUTF8CStringSize(jsStr);

	m_lastStringResult.resize(maxSize);

	size_t realSize = JSStringGetUTF8CString(
		jsStr,
		m_lastStringResult.data(),
		maxSize
	);

	JSStringRelease(jsStr);

	// realSize include \0
	if (realSize > 0)
		m_lastStringResult.resize(realSize - 1);
	else
		m_lastStringResult.clear();

	return m_lastStringResult.c_str();
}

}
