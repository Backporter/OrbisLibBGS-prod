
#include "../W/WeaponLeftSwingHandler.h"

namespace ConsoleRE
{
	bool WeaponLeftSwingHandler::ExecuteHandler(Actor* actor, const BSFixedString& param)
	{
		using func_t = decltype(&WeaponLeftSwingHandler::ExecuteHandler);
		Relocation<func_t> func("", 0x885F10);
		return func(this, actor, param);
	}
}