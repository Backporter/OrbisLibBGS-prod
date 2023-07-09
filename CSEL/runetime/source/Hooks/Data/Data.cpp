#include "Data.h"

#include "../../../Internal/PluginManger.h"

namespace Data
{
	uint32_t LoadScripts(ConsoleRE::TESDataHandler* a_this)
	{
		auto ret = a_this->LoadScripts();

		Internal::PluginManger::DispatchMessageToListener(0, Interface::MessagingInterface::kDataLoad, 0, 0, 0);

		return ret;
	}
}