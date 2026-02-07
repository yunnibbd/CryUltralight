#include "StdAfx.h"
#include "UltralightPlatformSettings.h"
#include <Ultralight/Ultralight.h>
#include <AppCore/Platform.h>
#include <CrySystem/ISystem.h>

namespace CryUltralight
{

void CUltralightPlatformSettings::Initial(int width, int height)
{
	m_width = width;
	m_height = height;
	ultralight::Config cfg;
	cfg.user_stylesheet = "body { background: transparent; }";
	ultralight::Platform::instance().set_config(cfg);

	char executableFolder[MAX_PATH];
	CryGetExecutableFolder(MAX_PATH, executableFolder);
	ultralight::Platform::instance().set_file_system(ultralight::GetPlatformFileSystem(executableFolder));
	ultralight::Platform::instance().set_font_loader(ultralight::GetPlatformFontLoader());
	ultralight::Platform::instance().set_logger(ultralight::GetDefaultLogger("ultralight.log"));
}

}
