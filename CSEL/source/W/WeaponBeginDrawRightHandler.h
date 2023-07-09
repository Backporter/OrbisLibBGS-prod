#pragma once

#include "../A/Actor.h"
#include "../B/BSFixedString.h"
#include "../I/IHandlerFunctor.h"

#include <stdint.h>

namespace ConsoleRE
{
	class WeaponBeginDrawRightHandler : public IHandlerFunctor<Actor, BSFixedString>
	{
	public:
		~WeaponBeginDrawRightHandler() override = default;

		// override (IHandlerFunctor)
		bool ExecuteHandler(Actor*, const BSFixedString&) override;

		bool operator()(Actor* actor, const BSFixedString& param)
		{
			return ExecuteHandler(actor, param);
		}
	};
	static_assert(sizeof(WeaponBeginDrawRightHandler) == 0x10);
}