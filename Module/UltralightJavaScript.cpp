#include "StdAfx.h"
#include "UltralightJavaScript.h"
#include "UltralightView.h"
#include <JavaScriptCore/JSRetainPtr.h>

namespace CryUltralight
{

void CUltralightJavaScript::Initial(CUltralightView* view)
{
	m_pUltralightView = view;
	view->m_view->set_load_listener(this);
}

void CUltralightJavaScript::SetDOMReadyCallBack(std::function<void()> cb)
{
	m_onDOMReadyCB = cb;
}

void CUltralightJavaScript::OnDOMReady(ultralight::View* caller, uint64_t frame_id, bool is_main_frame, const ultralight::String& url)
{
	if (!is_main_frame || !m_onDOMReadyCB)
		return;

	m_onDOMReadyCB();
}

}
