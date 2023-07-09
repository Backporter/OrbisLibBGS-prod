#include "../../../OrbisUtil/include/Relocation.h"

#include "../L/LeftHandSpellCastHandler.h"

namespace ConsoleRE
{
	bool LeftHandSpellCastHandler::ExecuteHandler(Actor* actor, const BSFixedString& param)
	{
		using func_t = decltype(&LeftHandSpellCastHandler::ExecuteHandler);
		Relocation<func_t> func("", 0x885D20);
		return func(this, actor, param);
	}
}