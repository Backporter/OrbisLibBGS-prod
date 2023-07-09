#include "../../../Internal/Interfaces/ScaleformInterface/ScaleformInterface.h"
#include <list>

namespace InventoryPlugin
{
	void RegisterPluginMenuSet(Interface::ScaleformInterface::InventoryCallback_t*);

	// used to interface this and fav.
	std::list<Interface::ScaleformInterface::InventoryCallback_t*>& getPluginList();
}
