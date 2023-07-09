#pragma once

#include "../A/Actor.h"
#include "../B/BSFixedString.h"
#include "../I/IHandlerFunctor.h"

#include <stdint.h>

namespace ConsoleRE
{
	class VoiceSpellCastHandler : public IHandlerFunctor<Actor, BSFixedString>
	{
	public:
		~VoiceSpellCastHandler() override = default;

		// override (IHandlerFunctor)
		bool ExecuteHandler(Actor* actor, const BSFixedString& param) override;

		bool operator()(Actor* actor, const BSFixedString& param)
		{
			return ExecuteHandler(actor, param);
		}
	};
	static_assert(sizeof(VoiceSpellCastHandler) == 0x10);
}