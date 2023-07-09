#include "InventoryPlugin.h"

namespace InventoryPlugin
{
	static std::list<Interface::ScaleformInterface::InventoryCallback_t*> pluginList;

	void RegisterPluginMenuSet(Interface::ScaleformInterface::InventoryCallback_t* a_callback) { pluginList.push_back(a_callback); }

	std::list<Interface::ScaleformInterface::InventoryCallback_t*>& getPluginList() { return pluginList; }
}
