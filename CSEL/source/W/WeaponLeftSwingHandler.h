#pragma once

#include "../../../OrbisUtil/include/Relocation.h"

#include "../A/Actor.h"
#include "../B/BSFixedString.h"
#include "../I/IHandlerFunctor.h"

#include <stdint.h>

namespace ConsoleRE
{
	class WeaponLeftSwingHandler : public IHandlerFunctor<Actor, BSFixedString>
	{
	public:
		~WeaponLeftSwingHandler() override = default;

		// override (IHandlerFunctor)
		bool ExecuteHandler(Actor*, const BSFixedString&) override;

		bool operator()(Actor* actor, const BSFixedString& param)
		{
			return ExecuteHandler(actor, param);
		}
	};
	static_assert(sizeof(WeaponLeftSwingHandler) == 0x10);
}