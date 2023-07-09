#include "../../../OrbisUtil/include/Relocation.h"

#include "../W/WeaponBeginDrawRightHandler.h"

namespace ConsoleRE
{
	bool WeaponBeginDrawRightHandler::ExecuteHandler(Actor* a_actor, const BSFixedString& a_str)
	{
		using func_t = decltype(&WeaponBeginDrawRightHandler::ExecuteHandler);
		Relocation<func_t> func("", 0x885FE0);
		return func(this, a_actor, a_str);
	}
}