#pragma once
#include <CryRenderer/IRenderer.h>

namespace CryUltralight
{

class CUltralightCaptureFrameListener
	: public ICaptureFrameListener
{
public:
	void Initial();

	virtual bool OnNeedFrameData(unsigned char*& pConvertedTextureBuf) override;
	virtual void OnFrameCaptured(void) override;
	virtual int  OnGetFrameWidth(void) override;
	virtual int  OnGetFrameHeight(void) override;
	virtual int  OnCaptureFrameBegin(int* pTexHandle) override;

private:
	bool m_initDown = false;
};

}
