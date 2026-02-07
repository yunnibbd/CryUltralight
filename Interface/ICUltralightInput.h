#pragma once


namespace CryUltralight
{

class ICUltralightView;

class ICUltralightInput
{
public:
	virtual void Initial(ICUltralightView* view) = 0;
	virtual void Enable() = 0;
	virtual void Disable() = 0;
};

}
