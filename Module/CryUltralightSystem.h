#pragma once
#include <CrySystem/ISystem.h>
#include <Ultralight/Ultralight.h>
#include <Ultralight/Bitmap.h>
#include <AppCore/Platform.h>
#include <CryInput/IInput.h>
#include "CryUltralightPlugin.h"
#include "ICryUltralightSystem.h"
#include "UltralightView.h"
#include "UltralightInput.h"
#include "UltralightJavaScript.h"

namespace CryUltralight
{

class CCryUltralightSystem
	: public ICryUltralightSystem
{
public:
	friend CPlugin_CryUltralight;

	virtual void Initial(int width, int height) override;
	virtual ICUltralightView* GetView() override { return mEnv->pUltralightView; };
	virtual ICUltralightInput* GetInput() override { return mEnv->pUltralightInput; }
	virtual ICUltralightJavaScript* GetJavaScriptContext() override { return mEnv->pUltralightJavaScript; }

private:
	int m_height = 0;
	int m_width = 0;
	bool m_canInput = false;
};

}
