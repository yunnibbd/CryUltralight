#include "StdAfx.h"
#include "CryUltralightSystem.h"
#include <CryRenderer/ITexture.h>
#include <CryInput/IHardwareMouse.h>
#include <CryRenderer/IRenderAuxGeom.h>
#include "UltralightCaptureFrameListener.h"
#include "UltralightRenderer.h"
#include "UltralightPlatformSettings.h"
#include "UltralightView.h"
#include "UltralightInput.h"
#include "UltralightJavaScript.h"

namespace CryUltralight
{

void CCryUltralightSystem::Initial(int width, int height)
{
	mEnv->pUltralightPlatformSettings = new CUltralightPlatformSettings();
	mEnv->pUltralightPlatformSettings->Initial(width, height);

	mEnv->pUltralightRenderer = new CUltralightRenderer();
	mEnv->pUltralightRenderer->Initial(mEnv->pUltralightPlatformSettings);

	mEnv->pUltralightView = new CUltralightView();
	mEnv->pUltralightView->Initial(mEnv->pUltralightRenderer->GetRenderer(), mEnv->pUltralightPlatformSettings);

	mEnv->pUltralightInput = new CUltralightInput();
	mEnv->pUltralightInput->Initial(mEnv->pUltralightView);

	mEnv->pUltralightJavaScript = new CUltralightJavaScript();
	mEnv->pUltralightJavaScript->Initial(mEnv->pUltralightView);

	//mEnv->pUltralightCaptureFrameListener = new CUltralightCaptureFrameListener();
	//mEnv->pUltralightCaptureFrameListener->Initial();
}

}
