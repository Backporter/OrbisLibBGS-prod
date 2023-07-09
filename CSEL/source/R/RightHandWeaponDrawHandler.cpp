#include "../../../OrbisUtil/include/Relocation.h"

#include "../R/RightHandWeaponDrawHandler.h"

namespace ConsoleRE
{
	bool RightHandWeaponDrawHandler::ExecuteHandler(Actor* actor, const BSFixedString& param)
	{
		using func_t = decltype(&RightHandWeaponDrawHandler::ExecuteHandler);
		Relocation<func_t> func("RightHandWeaponDrawHandler::2", 0x886240);
		return func(this, actor, param);
	}
}