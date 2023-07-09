#pragma once

#include "../A/Actor.h"
#include "../B/BSFixedString.h"
#include "../I/IHandlerFunctor.h"

#include <stdint.h>

namespace ConsoleRE
{
	// 0x10
	class RightHandWeaponSheatheHandler : public IHandlerFunctor<Actor, BSFixedString>
	{
	public:
		~RightHandWeaponSheatheHandler() override = default;

		// IHandlerFunctor
		bool ExecuteHandler(Actor* a_actor, const BSFixedString& a_str) override;

		bool operator()(Actor* actor, const BSFixedString& param)
		{
			return ExecuteHandler(actor, param);
		}
	};
	static_assert(sizeof(RightHandWeaponSheatheHandler) == 0x10);
}