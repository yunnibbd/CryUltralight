if (WINDOWS AND OPTION_ENGINE AND NOT OPTION_DEDICATED_SERVER)
	option(PLUGIN_CryUltralight "Enable CryUltralight plug-in for gui" ON)
else()
	option(PLUGIN_CryUltralight "Enable CryUltralight plug-in for gui" OFF)
endif()
	
if (NOT PLUGIN_CryUltralight)
	return()
endif()

start_sources()

sources_platform(ALL)
add_sources("NoUberFile"
	SOURCE_GROUP "Interface"
		"../Interface/ICryUltralightSystem.h"
		"../Interface/ICUltralightView.h"
		"../Interface/ICUltralightInput.h"
		"../Interface/ICryUltralightPlugin.h"
    SOURCE_GROUP "Root"
		"CryUltralightPlugin.cpp"
		"StdAfx.cpp"
		"CryUltralightPlugin.h"
		"PluginEnv.h"
		"StdAfx.h"
		"CryUltralightSystem.cpp"
		"CryUltralightSystem.h"
		"UltralightCaptureFrameListener.cpp"
		"UltralightCaptureFrameListener.h"
		"UltralightRenderer.cpp"
		"UltralightRenderer.h"
		"UltralightView.cpp"
		"UltralightView.h"
		"UltralightPlatformSettings.cpp"
		"UltralightPlatformSettings.h"
		"UltralightInput.cpp"
		"UltralightInput.h"
		"UltralightJavaScript.cpp"
		"UltralightJavaScript.h"
)

end_sources()

CryEngineModule(CryUltralight FORCE_SHARED PCH "StdAfx.cpp" SOLUTION_FOLDER "CryPlugins")

target_include_directories(${THIS_PROJECT} 
	PRIVATE 
		"${CRYENGINE_DIR}/Code/CryEngine/CryCommon"
		"${CRYENGINE_DIR}/Code/CryEngine/CryAction"
		"${CRYENGINE_DIR}/Code/CryEngine/CrySystem"
		"${CRYENGINE_DIR}/Code/CryEngine/CrySchematyc/Core/Interface"
	PUBLIC
		"${SDK_DIR}/_CustomSDKs/ultralight/include"
		../Interface
)

target_link_libraries(${THIS_PROJECT} PRIVATE
	${SDK_DIR}/_CustomSDKs/ultralight/lib/AppCore.lib
	${SDK_DIR}/_CustomSDKs/ultralight/lib/Ultralight.lib
	${SDK_DIR}/_CustomSDKs/ultralight/lib/UltralightCore.lib
	${SDK_DIR}/_CustomSDKs/ultralight/lib/WebCore.lib
)
