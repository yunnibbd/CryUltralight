#pragma once

#include <CrySystem/ICryPlugin.h>

namespace CryUltralight
{

class ICryUltralightSystem;

class ICryUltralightPlugin
	: public Cry::IEnginePlugin,
	  public ISystemEventListener
{
public:
	CRYINTERFACE_DECLARE_GUID(CryUltralight::ICryUltralightPlugin, "{EB0840F8-F5FD-42E7-83AD-DC3285EC5F2D}"_cry_guid)
	virtual ~ICryUltralightPlugin() {}

	virtual ICryUltralightSystem* GetCryUltralightSystem() = 0;
	virtual void StartRender() = 0;
	virtual void StopRender() = 0;
};

}
