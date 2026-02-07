#pragma once
#include <Ultralight/Ultralight.h>
#include "ICUltralightView.h"

namespace CryUltralight
{

class CUltralightRenderer;
class CUltralightJavaScript;
class CUltralightPlatformSettings;

class CUltralightView
	: public ICUltralightView
{
public:
	friend CUltralightRenderer;
	friend CUltralightJavaScript;
	virtual void Initial(ultralight::Renderer* renderer, CUltralightPlatformSettings* pSettings) override;
	virtual void LoadUrl(const char* url) override;
	virtual void LoadHTML(const char* html) override;
	virtual void Resize(uint32_t width, uint32_t height) override;
	virtual void Reload() override;
	virtual void FireMouseEvent(ultralight::MouseEvent& event) override;
	virtual void FireKeyEvent(ultralight::KeyEvent& event) override;
	virtual void FireScrollEvent(ultralight::ScrollEvent& event) override;

private:

	ultralight::RefPtr<ultralight::View>     m_view;
};

}
