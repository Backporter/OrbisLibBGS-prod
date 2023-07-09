#pragma once

#include "../A/Actor.h"
#include "../B/BSFixedString.h"
#include "../I/IHandlerFunctor.h"

#include <stdint.h>

namespace ConsoleRE
{
	class RightHandSpellFireHandler : public IHandlerFunctor<Actor, BSFixedString>
	{
	public:
		~RightHandSpellFireHandler() override = default;

		// override (IHandlerFunctor)
		bool ExecuteHandler(Actor* actor, const BSFixedString& param) override;

		bool operator()(Actor* actor, const BSFixedString& param)
		{
			return ExecuteHandler(actor, param);
		}
	public:
	};
	static_assert(sizeof(RightHandSpellFireHandler) == 0x10);
}