#pragma once

#include "ICUltralightJavaScript.h"
#include <Ultralight/Ultralight.h>
#include <functional>
#include <string>

namespace CryUltralight
{

class CUltralightView;

class CUltralightJavaScript 
	: public ultralight::LoadListener,
	  public ICUltralightJavaScript
{
public:
	CUltralightJavaScript();
	virtual void Initial(CUltralightView* view) override;
	virtual void SetReadyCallBack(std::function<void()> cb) override;
	virtual string EvaluateScript(const char* script) override;
	virtual void CallVoid(const char* name, const JSArgPlain* args, size_t count) override;
	virtual double CallNumber(const char* name, const JSArgPlain* args, size_t count) override;
	virtual bool CallBool(const char* name, const JSArgPlain* args, size_t count) override;
	virtual const char* CallString(const char* name, const JSArgPlain* args, size_t count) override;
	virtual void OnDOMReady(
		ultralight::View* caller,
		uint64_t frame_id, 
		bool is_main_frame,
		const ultralight::String& url) override;

private:
	class Impl;
	std::unique_ptr<Impl> m_impl;
	std::function<void()> m_onDOMReadyCB;
	std::string m_lastStringResult;
};

}
