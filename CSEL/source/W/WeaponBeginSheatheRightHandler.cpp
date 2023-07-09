#include "../../../OrbisUtil/include/Relocation.h"

#include "../W/WeaponBeginSheatheRightHandler.h"

namespace ConsoleRE
{
	bool WeaponBeginSheatheRightHandler::ExecuteHandler(Actor* actor, const BSFixedString& param)
	{
		using func_t = decltype(&WeaponBeginSheatheRightHandler::ExecuteHandler);
		Relocation<func_t> func("", 0x8860F0);
		return func(this, actor, param);
	}
}