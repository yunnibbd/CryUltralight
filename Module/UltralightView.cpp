#include "StdAfx.h"
#include "UltralightView.h" 
#include "UltralightPlatformSettings.h"

namespace CryUltralight
{


void CUltralightView::Initial(ultralight::Renderer* renderer, CUltralightPlatformSettings* pSettings)
{
	ultralight::ViewConfig viewCfg;
	viewCfg.is_accelerated = false;
	viewCfg.is_transparent = true;

	m_view = renderer->CreateView(pSettings->width(), pSettings->height(), viewCfg, nullptr);
}

void CUltralightView::LoadUrl(const char* url)
{
	m_view->LoadURL(url);
}

void CUltralightView::LoadHTML(const char* html)
{
	m_view->LoadHTML(html);
}

void CUltralightView::Resize(uint32_t width, uint32_t height)
{
	m_view->Resize(width, height);
}

void CUltralightView::Reload()
{
	m_view->Reload();
}

void CUltralightView::FireMouseEvent(ultralight::MouseEvent& event)
{
	m_view->FireMouseEvent(event);
}

void CUltralightView::FireKeyEvent(ultralight::KeyEvent& event)
{
	m_view->FireKeyEvent(event);
}

void CUltralightView::FireScrollEvent(ultralight::ScrollEvent& event)
{
	m_view->FireScrollEvent(event);
}

}
