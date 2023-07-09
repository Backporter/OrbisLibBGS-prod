#include "../../../OrbisUtil/include/Relocation.h"

#include "../R/RightHandSpellFireHandler.h"

namespace ConsoleRE
{
	bool RightHandSpellFireHandler::ExecuteHandler(Actor* actor, const BSFixedString& param)
	{
		using func_t = decltype(&RightHandSpellFireHandler::ExecuteHandler);
		Relocation<func_t> func("", 0x885BD0);
		return func(this, actor, param);
	}
}