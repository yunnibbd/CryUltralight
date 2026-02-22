#pragma once

namespace CryUltralight
{
class ICUltralightView;
class ICUltralightInput;
class ICUltralightJavaScript;

class ICryUltralightSystem
{
public:
	virtual void Initial(int width, int height) = 0;
	virtual ICUltralightView* GetView() = 0;
	virtual ICUltralightInput* GetInput() = 0;
	virtual ICUltralightJavaScript* GetJavaScriptContext() = 0;
};

}