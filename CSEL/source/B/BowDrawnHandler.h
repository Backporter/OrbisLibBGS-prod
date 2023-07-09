#pragma once

#include "../A/Actor.h"
#include "../B/BSFixedString.h"
#include "../I/IHandlerFunctor.h"

#include <stdint.h>

namespace ConsoleRE
{
	class BowDrawnHandler : public IHandlerFunctor<Actor, BSFixedString>
	{
	public:
		~BowDrawnHandler() override = default;

		// IHandlerFunctor
		bool ExecuteHandler(Actor*, const BSFixedString&) override;

		bool operator()(Actor* actor, const BSFixedString& param)
		{
			return ExecuteHandler(actor, param);
		}
	};
	static_assert(sizeof(BowDrawnHandler) == 0x10);
}