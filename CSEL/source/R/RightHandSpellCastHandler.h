#pragma once

#include "../A/Actor.h"
#include "../B/BSFixedString.h"
#include "../I/IHandlerFunctor.h"

#include <stdint.h>

namespace ConsoleRE
{
	class RightHandSpellCastHandler : public IHandlerFunctor<Actor, BSFixedString>
	{
	public:
		~RightHandSpellCastHandler() override = default;

		// override (IHandlerFunctor)
		bool ExecuteHandler(Actor* a_actor, const BSFixedString& a_str) override;

		bool operator()(Actor* actor, const BSFixedString& param)
		{
			return ExecuteHandler(actor, param);
		}
	};
	static_assert(sizeof(RightHandSpellCastHandler) == 0x10, "");
}