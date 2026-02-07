#pragma once
#include <Ultralight/Ultralight.h>

namespace CryUltralight
{

class CUltralightPlatformSettings;

class ICUltralightView
{
public:
	virtual void Initial(ultralight::Renderer* renderer, CUltralightPlatformSettings* pSettings) = 0;
	virtual void LoadUrl(const char* url) = 0;
	virtual void LoadHTML(const char* html) = 0;
	virtual void Resize(uint32_t width, uint32_t height) = 0;
	virtual void Reload() = 0;
	virtual void FireMouseEvent(ultralight::MouseEvent& event) = 0;
	virtual void FireKeyEvent(ultralight::KeyEvent& event) = 0;
	virtual void FireScrollEvent(ultralight::ScrollEvent& event) = 0;
};

}
