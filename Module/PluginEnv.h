#pragma once

namespace CryUltralight
{
	class ICryUltralightSystem;
	class CUltralightPlatformSettings;
	class CUltralightCaptureFrameListener;
	class CUltralightRenderer;
	class CUltralightView;
	class CUltralightInput;
	class CUltralightJavaScript;
	
	// Global plugin environment
	struct SPluginEnv
	{
		ICryUltralightSystem*				pUltralightSystem = nullptr;

		CUltralightPlatformSettings*		pUltralightPlatformSettings = nullptr;

		CUltralightCaptureFrameListener*	pUltralightCaptureFrameListener = nullptr;

		CUltralightRenderer*				pUltralightRenderer = nullptr;

		CUltralightView*					pUltralightView = nullptr;

		CUltralightInput*					pUltralightInput = nullptr;

		CUltralightJavaScript*				pUltralightJavaScript = nullptr;
	};

	extern SPluginEnv* mEnv;
}