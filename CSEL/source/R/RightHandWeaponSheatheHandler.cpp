#include "../../../OrbisUtil/include/Relocation.h"

#include "../R/RightHandWeaponSheatheHandler.h"

namespace ConsoleRE
{
	bool RightHandWeaponSheatheHandler::ExecuteHandler(Actor* actor, const BSFixedString& param)
	{
		using func_t = decltype(&RightHandWeaponSheatheHandler::ExecuteHandler);
		Relocation<func_t> func("", 0x886420);
		return func(this, actor, param);
	}
}