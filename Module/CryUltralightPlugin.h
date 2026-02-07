#pragma once

#include <CrySystem/ICryPlugin.h>
#include <CryEntitySystem/IEntityClass.h>
#include "ICryUltralightPlugin.h"

namespace CryUltralight
{
class  CPlugin_CryUltralight final
	: public ICryUltralightPlugin

{
public:
	CRYINTERFACE_BEGIN()
	CRYINTERFACE_ADD(CPlugin_CryUltralight)
	CRYINTERFACE_ADD(Cry::IEnginePlugin)
	CRYINTERFACE_END()

	CRYGENERATE_SINGLETONCLASS_GUID(CryUltralight::CPlugin_CryUltralight, "CryUltralight", "{3b7a3705-8d71-4adb-8e9c-bd0557ced126}"_cry_guid)

	PLUGIN_FLOWNODE_REGISTER;
	PLUGIN_FLOWNODE_UNREGISTER;

	virtual ~CPlugin_CryUltralight();
public:
	// ICryPlugin
	virtual const char* GetName() const override { return "CPlugin_CryUltralight"; }
	virtual const char* GetCategory() const override { return "Render"; }
	virtual bool        Initialize(SSystemGlobalEnvironment& env, const SSystemInitParams& initParams) override;
	// ~ICryPlugin

	// ISystemEventListener
	virtual void        OnSystemEvent(ESystemEvent event, UINT_PTR wparam, UINT_PTR lparam) override;
	// ~ISystemEventListener

	virtual void MainUpdate(float frameTime) override;

	virtual ICryUltralightSystem* GetCryUltralightSystem() override;
	virtual void StartRender() override;
	virtual void StopRender() override;
};
}

using namespace CryUltralight;