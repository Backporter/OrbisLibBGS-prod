#pragma once

#include "../A/Actor.h"
#include "../B/BSFixedString.h"
#include "../I/IHandlerFunctor.h"

#include <stdint.h>

namespace ConsoleRE
{
	class VoiceSpellFireHandler : public IHandlerFunctor<Actor, BSFixedString>
	{
	public:
		~VoiceSpellFireHandler() override = default;

		// override (IHandlerFunctor)
		bool ExecuteHandler(Actor* actor, const BSFixedString& param) override;

		bool operator()(Actor* actor, const BSFixedString& param)
		{
			return ExecuteHandler(actor, param);
		}
	};
	static_assert(sizeof(VoiceSpellFireHandler) == 0x10);
}