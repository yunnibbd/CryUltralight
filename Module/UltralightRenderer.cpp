#include "StdAfx.h"
#include "UltralightRenderer.h"
#include "UltralightPlatformSettings.h"
#include "UltralightView.h"
#include <CryRenderer/IRenderAuxGeom.h>

namespace CryUltralight
{

void CUltralightRenderer::Initial(CUltralightPlatformSettings* pSettings)
{
	m_pSettings = pSettings;
	m_renderer = ultralight::Renderer::Create();
}

void CUltralightRenderer::Update()
{
	m_renderer->Update();
}

void CUltralightRenderer::RenderOneFrame()
{
	///
	/// Notify the renderer that the physical display has refreshed and
	/// any active animations should be updated.
	///
	m_renderer->RefreshDisplay(0);

	///
	/// Render all active Views (this updates the Surface for each View).
	///
	m_renderer->Render();

	///
	/// Get the Surface as a BitmapSurface (the default implementation).
	///
	ultralight::BitmapSurface* surface = (ultralight::BitmapSurface*)(mEnv->pUltralightView->m_view->surface());

	///
	/// Check if our Surface is dirty (pixels have changed).
	///
	if (!surface->dirty_bounds().IsEmpty()) {
		if (m_tex != nullptr)
		{
			gEnv->pRenderer->RemoveTexture(m_tex->GetTextureID());
			m_tex = nullptr;
		}
		///
		/// Psuedo-code to upload Surface's bitmap to GPU texture.
		///
		CopyBitmapToTexture(surface->bitmap());

		///
		/// Clear the dirty bounds.
		///
		surface->ClearDirtyBounds();
	}
	IRenderAuxImage::Draw2dImage(
		0,
		0,
		m_tex->GetWidth(),
		m_tex->GetHeight(),
		m_tex->GetTextureID(),
		0.0f,
		1.0f,
		1.0f,
		0.0f,
		0.0f,
		1,
		1,
		1,
		1.0f,
		1
	);
}

void CUltralightRenderer::CopyBitmapToTexture(ultralight::RefPtr<ultralight::Bitmap> bitmap)
{
	///
	/// Lock the Bitmap to retrieve the raw pixels.
	/// The format is BGRA, 8-bpp, premultiplied alpha.
	///
	void* pixels = bitmap->LockPixels();

	///
	/// Get the bitmap dimensions.
	///
	uint32_t width = bitmap->width();
	uint32_t height = bitmap->height();
	uint32_t stride = bitmap->row_bytes();
	const uint32 tightStride = width * 4;

	const bool tightlyPacked = (stride == tightStride);
	const uint8* uploadPtr = nullptr;

	if (tightlyPacked)
	{
		uploadPtr = static_cast<const uint8*>(pixels);
	}
	else
	{
		if (m_cpuBuffer.size() != tightStride * height)
			m_cpuBuffer.resize(tightStride * height);

		const uint8* src = static_cast<const uint8*>(pixels);
		uint8* dst = m_cpuBuffer.data();

		for (uint32 y = 0; y < height; ++y)
		{
			memcpy(dst, src, tightStride);
			src += stride;
			dst += tightStride;
		}

		uploadPtr = m_cpuBuffer.data();
	}

	///
	/// Psuedo-code to upload our pixels to a GPU texture.
	///
	m_tex = gEnv->pRenderer->CreateTexture(
		"BitmapTexture",
		width,
		height,
		1,
		(unsigned char*)uploadPtr,
		eTF_B8G8R8A8,
		FT_NOMIPS | FT_DONT_STREAM
	);

	///
	/// Unlock the Bitmap when we are done.
	///
	bitmap->UnlockPixels();
}

}

