#include "../../../OrbisUtil/include/Relocation.h"

#include "../B/BowDrawnHandler.h"

namespace ConsoleRE
{
	bool BowDrawnHandler::ExecuteHandler(Actor* actor, const BSFixedString& param)
	{
		using func_t = decltype(&BowDrawnHandler::ExecuteHandler);
		Relocation<func_t> func("", 0x8879E0);
		return func(this, actor, param);
	}
}