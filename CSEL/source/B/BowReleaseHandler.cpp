#include "../../../OrbisUtil/include/Relocation.h"

#include "../B/BowReleaseHandler.h"

namespace ConsoleRE
{
	bool BowReleaseHandler::ExecuteHandler(Actor* actor, const BSFixedString& param)
	{
		using func_t = decltype(&BowReleaseHandler::ExecuteHandler);
		Relocation<func_t> func("", 0x887A20);
		return func(this, actor, param);
	}
}