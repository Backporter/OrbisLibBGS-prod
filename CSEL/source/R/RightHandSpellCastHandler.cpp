#include "../../../OrbisUtil/include/Relocation.h"

#include "../R/RightHandSpellCastHandler.h"

namespace ConsoleRE
{
	bool RightHandSpellCastHandler::ExecuteHandler(Actor* a_actor, const BSFixedString& a_str)
	{
		using func_t = decltype(&RightHandSpellCastHandler::ExecuteHandler);
		Relocation<func_t> func("", 0x885D70);
		return func(this, a_actor, a_str);
	}
}