#pragma once
#include <Ultralight/Ultralight.h>
#include <CryRenderer/ITexture.h>

namespace CryUltralight
{

class CUltralightPlatformSettings;

class CUltralightRenderer
{
public:
	void Initial(CUltralightPlatformSettings* pSettings);

	void Update();

	ultralight::Renderer* GetRenderer() { return m_renderer.get(); }

	void RenderOneFrame();
	void CopyBitmapToTexture(ultralight::RefPtr<ultralight::Bitmap> bitMap);
private:
	ultralight::RefPtr<ultralight::Renderer> m_renderer;
	ITexture* m_tex;
	CUltralightPlatformSettings* m_pSettings;
	std::vector<uint8_t> m_cpuBuffer;
};

}
