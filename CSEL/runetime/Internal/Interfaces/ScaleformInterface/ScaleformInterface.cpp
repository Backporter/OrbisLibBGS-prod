#include "ScaleformInterface.h"

#include "../../../source/Hooks/Scaleform/ScaleformExt.h"
#include "../../../source/Hooks/CraftingSubMenus/InventoryPlugin.h"

namespace Interface
{
	int	ScaleformInterface::ScaleformPluginInfo::GetVersion()
	{
		return Version;
	}

	int	ScaleformInterface::GetInterfaceVersion()												
	{
		return ScaleformInterface::Version;							 
	}
	
	bool ScaleformInterface::RegisterScaleformCallback(const char* a_plugin, CallBack_t* a_func) 
	{ 
		return Scaleform::RegisterScaleformCallback(a_plugin, a_func); 
	}
	
	void ScaleformInterface::RegisterInventoryCallback(InventoryCallback_t* a_func)				
	{ 
		return InventoryPlugin::RegisterPluginMenuSet(a_func);		 
	}

}