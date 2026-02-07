#include "StdAfx.h"
#include "CryUltralightPlugin.h"

#include <CrySchematyc/Env/IEnvRegistry.h>
#include <CrySchematyc/Env/EnvPackage.h>
#include <CrySchematyc/Utils/SharedString.h>
#include <CrySchematyc/CoreAPI.h>

#include <CryCore/Platform/platform_impl.inl>
#include <CrySystem/ConsoleRegistration.h>

#include <CryInput/IHardwareMouse.h>

#include "CryUltralightSystem.h"
#include "UltralightRenderer.h"
#include "UltralightCaptureFrameListener.h"


CPlugin_CryUltralight::~CPlugin_CryUltralight()
{
	if (gEnv->pSystem != nullptr && !gEnv->IsDedicated())
	{
		gEnv->pSystem->GetISystemEventDispatcher()->RemoveListener(this);
	}

#ifndef CRY_IS_MONOLITHIC_BUILD 
	if (gEnv->pSchematyc != nullptr && !gEnv->IsDedicated())
	{
		gEnv->pSchematyc->GetEnvRegistry().DeregisterPackage(CPlugin_CryUltralight::GetCID());
	}
#endif
}

bool CPlugin_CryUltralight::Initialize(SSystemGlobalEnvironment& env, const SSystemInitParams& initParams)
{
	if (gEnv->pSystem != nullptr && !gEnv->IsDedicated())
	{
		gEnv->pSystem->GetISystemEventDispatcher()->RegisterListener(this, "CCryUltralight_Listener");
	}

	if (!gEnv->IsDedicated())
	{
		mEnv->pUltralightSystem = new CCryUltralightSystem();
	}

	return true;
}

void CPlugin_CryUltralight::OnSystemEvent(ESystemEvent event, UINT_PTR wparam, UINT_PTR lparam)
{
	if (gEnv->IsDedicated())
	{
		return;
	}

	switch (event)
	{
	case ESYSTEM_EVENT_GAME_POST_INIT_DONE:
	{
		StartRender();
		break;
	}
	default:
		break;
	}
}

void CPlugin_CryUltralight::MainUpdate(float frameTime)
{
	if (!mEnv->pUltralightRenderer)
		return;
	mEnv->pUltralightRenderer->Update();
	mEnv->pUltralightRenderer->RenderOneFrame();
}

ICryUltralightSystem* CPlugin_CryUltralight::GetCryUltralightSystem()
{
	return mEnv->pUltralightSystem;
}

void CPlugin_CryUltralight::StartRender()
{
	EnableUpdate(IEnginePlugin::EUpdateStep::MainUpdate, true);
}

void CPlugin_CryUltralight::StopRender()
{
	EnableUpdate(IEnginePlugin::EUpdateStep::MainUpdate, false);
}

CRYREGISTER_SINGLETON_CLASS(CPlugin_CryUltralight)
