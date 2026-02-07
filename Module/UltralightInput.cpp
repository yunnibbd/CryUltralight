#include "StdAfx.h"
#include "UltralightInput.h"
#include <CryInput/IHardwareMouse.h>
#include <Ultralight/Ultralight.h>
#include <Ultralight/Bitmap.h>
#include <AppCore/Platform.h>

namespace CryUltralight
{

void CUltralightInput::Initial(ICUltralightView* view)
{
	m_pCUltralightView = view;
}

void CUltralightInput::Enable()
{
	if (m_isEnable)
		return;
	gEnv->pInput->AddEventListener(this);
	m_isEnable = true;
}

void CUltralightInput::Disable()
{
	if (!m_isEnable)
		return;
	gEnv->pInput->RemoveEventListener(this);
	m_isEnable = false;
}

bool CUltralightInput::OnInputEvent(const SInputEvent& e)
{
	CRY_ASSERT(m_pCUltralightView, "input not initial!");
	// ----------------------------
	// Mouse
	// ----------------------------
	if (e.deviceType == eIDT_Mouse)
	{
		// Mouse Move
		if (e.keyId == eKI_MouseX || e.keyId == eKI_MouseY)
		{
			ultralight::MouseEvent evt;
			evt.type = ultralight::MouseEvent::kType_MouseMoved;
			float posX = 0;
			float posY = 0;
			gEnv->pHardwareMouse->GetHardwareMouseClientPosition(&posX, &posY);
			evt.x = (int)posX;
			evt.y = (int)posY;
			m_pCUltralightView->FireMouseEvent(evt);
			return false;
		}

		// Mouse Buttons
		if (e.keyId == eKI_Mouse1 ||
			e.keyId == eKI_Mouse2 ||
			e.keyId == eKI_Mouse3)
		{
			ultralight::MouseEvent evt;
			evt.type = (e.state == eIS_Pressed)
				? ultralight::MouseEvent::kType_MouseDown
				: ultralight::MouseEvent::kType_MouseUp;

			if (e.keyId == eKI_Mouse1)
				evt.button = ultralight::MouseEvent::kButton_Left;
			else if (e.keyId == eKI_Mouse2)
				evt.button = ultralight::MouseEvent::kButton_Right;
			else
				evt.button = ultralight::MouseEvent::kButton_Middle;

			float posX = 0;
			float posY = 0;
			gEnv->pHardwareMouse->GetHardwareMouseClientPosition(&posX, &posY);
			evt.x = (int)posX;
			evt.y = (int)posY;
			m_pCUltralightView->FireMouseEvent(evt);
			return false;
		}

		// Mouse Wheel
		if (e.keyId == eKI_MouseWheelUp ||
			e.keyId == eKI_MouseWheelDown)
		{
			ultralight::ScrollEvent evt;
			evt.type = ultralight::ScrollEvent::kType_ScrollByPixel;
			evt.delta_x = 0;
			evt.delta_y = int(e.value * 120.f);
			m_pCUltralightView->FireScrollEvent(evt);
			return false;
		}
	}

	// ----------------------------
	// Keyboard
	// ----------------------------
	if (e.deviceType == eIDT_Keyboard)
	{
		// Key down / up
		ultralight::KeyEvent evt;
		if (e.state == eIS_Pressed)
		{
			ultralight::KeyEvent evt;
			evt.type = ultralight::KeyEvent::kType_Char;
			evt.text = e.keyName.c_str();
			m_pCUltralightView->FireKeyEvent(evt);
		}
		return false;
	}

	return false;
}

int CUltralightInput::CryKeyToUltralight(EKeyId key)
{
	switch (key)
	{
	case eKI_Backspace: return ultralight::KeyCodes::GK_BACK;
	case eKI_Enter:     return ultralight::KeyCodes::GK_RETURN;
	case eKI_Tab:       return ultralight::KeyCodes::GK_TAB;
	case eKI_Escape:    return ultralight::KeyCodes::GK_ESCAPE;

	case eKI_Left:      return ultralight::KeyCodes::GK_LEFT;
	case eKI_Right:     return ultralight::KeyCodes::GK_RIGHT;
	case eKI_Up:        return ultralight::KeyCodes::GK_UP;
	case eKI_Down:      return ultralight::KeyCodes::GK_DOWN;

	case eKI_LShift:
	case eKI_RShift:    return ultralight::KeyCodes::GK_SHIFT;
	case eKI_LCtrl:
	case eKI_RCtrl:     return ultralight::KeyCodes::GK_CONTROL;
	case eKI_LAlt:
	case eKI_RAlt:      return ultralight::KeyCodes::GK_MENU;
	default:
		break;
	}
	return 0;
}


}
