#include "../../../OrbisUtil/include/Relocation.h"

#include "../T/TESQuest.h"

namespace ConsoleRE
{
	bool TESQuest::EnsureQuestStarted(bool& a_result, bool a_startNow)
	{
		using func_t = decltype(&TESQuest::EnsureQuestStarted);
		Relocation<func_t> func("", 0x32FFE0);
		return func(this, a_result, a_startNow);
	}
}