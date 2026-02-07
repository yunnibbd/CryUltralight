#pragma once
#include "ICUltralightInput.h"
#include "ICUltralightView.h"
#include <CryInput/IInput.h>

namespace CryUltralight
{

class CUltralightInput
	: public IInputEventListener,
	  public ICUltralightInput
{
public:
	virtual void Initial(ICUltralightView* view) override;
	virtual void Enable() override;
	virtual void Disable() override;
	virtual bool OnInputEvent(const SInputEvent& event) override;

protected:
	int CryKeyToUltralight(EKeyId key);
private:
	ICUltralightView* m_pCUltralightView = nullptr;
	bool m_isEnable = false;
};

}
