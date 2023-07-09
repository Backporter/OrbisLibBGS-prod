#pragma once

#include "../A/Actor.h"
#include "../B/BSFixedString.h"
#include "../I/IHandlerFunctor.h"

namespace ConsoleRE
{
	class LeftHandSpellFireHandler : public IHandlerFunctor<Actor, BSFixedString>
	{
	public:
		~LeftHandSpellFireHandler() override = default;
		
		// override (IHandlerFunctor)
		bool ExecuteHandler(Actor* a_actor, const BSFixedString& a_str) override;

		bool operator()(Actor* actor, const BSFixedString& param)
		{
			return ExecuteHandler(actor, param);
		}
	};
	static_assert(sizeof(LeftHandSpellFireHandler) == 0x10);
}