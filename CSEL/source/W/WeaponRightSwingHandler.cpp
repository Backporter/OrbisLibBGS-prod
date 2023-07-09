#include "../../../OrbisUtil/include/Relocation.h"

#include "../W/WeaponRightSwingHandler.h"

namespace ConsoleRE
{
	bool WeaponRightSwingHandler::ExecuteHandler(Actor* actor, const BSFixedString& param)
	{
		using func_t = decltype(&WeaponRightSwingHandler::ExecuteHandler);
		Relocation<func_t> func("", 0x885E40);
		return func(this, actor, param);
	}
}