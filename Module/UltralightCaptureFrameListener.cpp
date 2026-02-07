#include "StdAfx.h"
#include "UltralightRenderer.h"
#include "UltralightCaptureFrameListener.h"

namespace CryUltralight
{

void CUltralightCaptureFrameListener::Initial()
{
	gEnv->pRenderer->RegisterCaptureFrame(this);
}

bool CUltralightCaptureFrameListener::OnNeedFrameData(unsigned char*& pConvertedTextureBuf)
{
	return true;
}

void CUltralightCaptureFrameListener::OnFrameCaptured(void)
{
	if (!m_initDown)
		return;
	mEnv->pUltralightRenderer->Update();
	mEnv->pUltralightRenderer->RenderOneFrame();
}

int  CUltralightCaptureFrameListener::OnGetFrameWidth(void)
{
	return 0;
}

int  CUltralightCaptureFrameListener::OnGetFrameHeight(void)
{
	return 0;
}

int  CUltralightCaptureFrameListener::OnCaptureFrameBegin(int* pTexHandle)
{
	return 1;
}


}
