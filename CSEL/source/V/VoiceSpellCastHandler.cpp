#include "../../../OrbisUtil/include/Relocation.h"

#include "../V/VoiceSpellCastHandler.h"

namespace ConsoleRE
{
	bool VoiceSpellCastHandler::ExecuteHandler(Actor* actor, const BSFixedString& param)
	{
		using func_t = uint8_t(decltype(this), Actor*, const BSFixedString&);
		Relocation<func_t*> func("", 0x885DC0);
		return func(this, actor, param);
	}
}