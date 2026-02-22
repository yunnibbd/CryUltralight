#include "StdAfx.h"
#include "UltralightPlatformSettings.h"
#include <Ultralight/Ultralight.h>
#include <AppCore/Platform.h>
#include <CrySystem/ISystem.h>
#include <CrySystem/IProjectManager.h>

namespace CryUltralight
{

void CUltralightPlatformSettings::Initial(int width, int height)
{
	m_width = width;
	m_height = height;
	ultralight::Config cfg;
	cfg.user_stylesheet = "body { background: transparent; }";
	ultralight::Platform::instance().set_config(cfg);
	string content;
	const char* assetPath = gEnv->pSystem->GetIProjectManager()->GetCurrentAssetDirectoryAbsolute();
	ultralight::Platform::instance().set_file_system(ultralight::GetPlatformFileSystem(assetPath));
	ultralight::Platform::instance().set_font_loader(ultralight::GetPlatformFontLoader());
	ultralight::Platform::instance().set_logger(ultralight::GetDefaultLogger("ultralight.log"));
}

}
