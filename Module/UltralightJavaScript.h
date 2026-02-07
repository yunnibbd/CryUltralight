#pragma once

#include <Ultralight/Ultralight.h>
#include <functional>

namespace CryUltralight
{

class CUltralightView;

class CUltralightJavaScript 
	: public ultralight::LoadListener
{
public:
	void Initial(CUltralightView* view);
	void SetDOMReadyCallBack(std::function<void()> cb);
	//void CallJSFunction(const char* name);
	
	virtual void OnDOMReady(
		ultralight::View* caller,
		uint64_t frame_id, 
		bool is_main_frame,
		const ultralight::String& url) override;

private:
	CUltralightView* m_pUltralightView = nullptr;
	std::function<void()> m_onDOMReadyCB;
};

}
