#include "../../../OrbisUtil/include/Relocation.h"

#include "../V/VoiceSpellFireHandler.h"

namespace ConsoleRE
{
	bool VoiceSpellFireHandler::ExecuteHandler(Actor* actor, const BSFixedString& param)
	{
		using func_t = decltype(&VoiceSpellFireHandler::ExecuteHandler);
		Relocation<func_t> func("", 0x885C10);
		return func(this, actor, param);
	}
}