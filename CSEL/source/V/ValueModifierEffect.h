#pragma once

#include "../A/ActiveEffect.h"

namespace ConsoleRE
{
	class ValueModifierEffect : public ActiveEffect
	{
	public:
		virtual ~ValueModifierEffect();
	public:
		uint32_t actorValue;
	};
}