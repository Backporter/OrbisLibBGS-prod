#include "../B/BGSSaveLoadManager.h"

namespace ConsoleRE
{
	bool BGSSaveLoadManager::Save_Impl(int32_t a_deviceID, uint32_t a_outputStats, const char* a_fileName)
	{
		using func_t = decltype(&BGSSaveLoadManager::Save_Impl);
		Relocation<func_t> func("", 0x677BA0);
		return func(this, a_deviceID, a_outputStats, a_fileName);
	}

	bool BGSSaveLoadManager::Load_Impl(const char* a_fileName, int32_t a_deviceID, uint32_t a_outputStats, bool a_checkForMods)
	{
		using func_t = decltype(&BGSSaveLoadManager::Load_Impl);
		Relocation<func_t> func("", 0x67A700);
		return func(this, a_fileName, a_deviceID, a_outputStats, a_checkForMods);
	}
}