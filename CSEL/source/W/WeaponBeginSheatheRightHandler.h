#pragma once

#include "../A/Actor.h"
#include "../B/BSFixedString.h"
#include "../I/IHandlerFunctor.h"

#include <stdint.h>

namespace ConsoleRE
{
	class WeaponBeginSheatheRightHandler : public IHandlerFunctor<Actor, BSFixedString>
	{
	public:
		~WeaponBeginSheatheRightHandler() override = default;

		// override (IHandlerFunctor)
		bool ExecuteHandler(Actor*, const BSFixedString&) override;

		bool operator()(Actor* actor, const BSFixedString& param)
		{
			return ExecuteHandler(actor, param);
		}
	public:
	};
	static_assert(sizeof(WeaponBeginSheatheRightHandler) == 0x10);
}