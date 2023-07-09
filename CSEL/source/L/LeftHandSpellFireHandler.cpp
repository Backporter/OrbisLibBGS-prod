#include "../../../OrbisUtil/include/Relocation.h"

#include "../L/LeftHandSpellFireHandler.h"

namespace ConsoleRE
{
	bool LeftHandSpellFireHandler::ExecuteHandler(Actor* a_actor, const BSFixedString& a_str)
	{
		using func_t = decltype(&LeftHandSpellFireHandler::ExecuteHandler);
		Relocation<func_t> func("", 0x885B80);
		return func(this, a_actor, a_str);
	}
}